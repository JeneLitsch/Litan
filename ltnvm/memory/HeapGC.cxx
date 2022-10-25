#include "Heap.hxx"
#include "ltnvm/type_check.hxx"
namespace ltn::vm {
	void Heap::collect_garbage(const Stack & stack, const Register & reg, const std::vector<Value> & globals) {
		mark(stack.get_container());
		mark(reg.get_container());
		mark(globals);
		sweep();
	}

	void Heap::mark(const std::span<const Value> values) {
		for(const auto & value : values) {
			this->mark(value);
		}
	}

	void Heap::mark(const std::deque<Value> & values) {
		for(const auto & value : values) {
			this->mark(value);
		}
	}

	void Heap::mark(const Value & value) {
		if(is_array(value))   return this->mark_array(value);
		if(is_string(value))  return this->mark_default(value);
		
		if(is_istream(value)) return this->mark_default(value);
		if(is_ostream(value)) return this->mark_default(value);
		
		if(is_fxptr(value))   return this->mark_fxptr(value);

		if(is_clock(value))    return this->mark_default(value);
		
		if(is_struct(value))  return this->mark_struct(value);

		if(is_stack(value))   return this->mark_deque(value);
		if(is_queue(value))   return this->mark_deque(value);

		if(is_map(value))     return this->mark_map(value);
		
		if(is_rng(value))     return this->mark_default(value);
	}

	void Heap::mark_array(const Value & ref) {
		auto & obj = this->get(ref.u);
		if(!obj.marked) {
			auto & arr = this->read<Array>(ref.u);
			obj.marked = true;
			this->mark(arr.arr);
		}
	}

	void Heap::mark_fxptr(const Value & value) {
		auto & obj = get(value.u);
		if(!obj.marked) {
			auto & fx = this->read<FxPointer>(value.u);
			obj.marked = true;
			this->mark(fx.captured);
		}
	}


	void Heap::mark_struct(const Value & value) {
		auto & obj = get(value.u);
		if(!obj.marked) {
			auto & s = this->read<Struct>(value.u);
			obj.marked = true;
			for(const auto & [key, value] : s.members) {
				this->mark(value);
			}
		}
	}


	void Heap::mark_deque(const Value & value) {
		auto & obj = get(value.u);
		if(!obj.marked) {
			auto & deque = this->read<Deque>(value.u);
			obj.marked = true;
			this->mark(deque.get());
		}
	}


	void Heap::mark_map(const Value & value) {
		auto & obj = get(value.u);
		if(!obj.marked) {
			auto & map = this->read<Map>(value.u).get();
			obj.marked = true;
			for(auto & [key, value] : map) {
				this->mark(key);
				this->mark(value);
			}
		}
	}


	void Heap::mark_default(const Value & value) {
		auto & obj = this->get(value.u);
		obj.marked = true;
	}


	void Heap::sweep() {
		std::uint64_t idx = 0;
		for(auto & obj : this->objects) {
			if(obj.marked) {
				obj.marked = false;
			}
			else if(!std::get_if<std::monostate>(&obj.obj)) {
				obj.obj = std::monostate();
				this->reuse.push(idx);
			}
			idx++;
		}
	}
}