#include "Heap.hxx"
#include "ltnvm/TypeCheck.hxx"
namespace ltn::vm {
	void Heap::collectGarbage(const Stack & stack, const Register & reg) {
		mark(stack.getContainer());
		mark(reg.getContainer());
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
		if(isArr(value))     return this->markArray(value);
		if(isStr(value))     return this->markDefault(value);
		
		if(isIStream(value)) return this->markDefault(value);
		if(isOStream(value)) return this->markDefault(value);
		
		if(isFxPtr(value))   return this->markFxPtr(value);

		if(isClock(value))   return this->markDefault(value);
		
		if(isStruct(value))  return this->markStruct(value);
		if(isRange(value))   return this->markRange(value);

		if(isStack(value))   return this->markDeque(value);
		if(isQueue(value))   return this->markDeque(value);
	}

	void Heap::markArray(const Value & ref) {
		auto & obj = this->get(ref.u);
		if(!obj.marked) {
			auto & arr = this->read<Array>(ref.u);
			obj.marked = true;
			this->mark(arr.arr);
		}
	}

	void Heap::markFxPtr(const Value & value) {
		auto & obj = get(value.u);
		if(!obj.marked) {
			auto & fx = this->read<FxPointer>(value.u);
			obj.marked = true;
			this->mark(fx.captured);
		}
	}


	void Heap::markStruct(const Value & value) {
		auto & obj = get(value.u);
		if(!obj.marked) {
			auto & s = this->read<Struct>(value.u);
			obj.marked = true;
			for(const auto & [key, value] : s.members) {
				this->mark(value);
			}
		}
	}


	void Heap::markRange(const Value & value) {
		auto & obj = get(value.u);
		if(!obj.marked) {
			auto & range = this->read<Range>(value.u);
			obj.marked = true;
			this->mark(Value{range.array, Value::Type::ARRAY});
		}
	}

	
	void Heap::markDeque(const Value & value) {
		auto & obj = get(value.u);
		if(!obj.marked) {
			auto & deque = this->read<Deque>(value.u);
			obj.marked = true;
			this->mark(deque.get());
		}
	}


	void Heap::markDefault(const Value & value) {
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