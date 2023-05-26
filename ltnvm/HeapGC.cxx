#include "Heap.hxx"
#include "ltnvm/utils/type_check.hxx"
namespace ltn::vm {
	void Heap::mark(const Array & values) {
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
		switch (value.type) {
			case Value::Type::NVLL:          return; // no gc required
			case Value::Type::BOOL:          return; // no gc required
			case Value::Type::INT:           return; // no gc required
			case Value::Type::FLOAT:         return; // no gc required
			case Value::Type::CHAR:          return; // no gc required
			case Value::Type::ARRAY:         return this->mark_array(value);
			case Value::Type::STRING:        return this->mark_string(value);
			case Value::Type::TUPLE:         return this->mark_array(value);
			case Value::Type::ISTREAM:       return this->mark_istream(value);
			case Value::Type::ITERATOR:      return this->mark_iterator(value);
			case Value::Type::ITERATOR_STOP: return; // no gc required
			case Value::Type::OSTREAM:       return this->mark_ostream(value);
			case Value::Type::FX_PTR:        return this->mark_fxptr(value);
			case Value::Type::CLOCK:         return this->mark_clock(value);
			case Value::Type::STRUCT:        return this->mark_struct(value);
			case Value::Type::QUEUE:         return this->mark_deque(value);
			case Value::Type::STACK:         return this->mark_deque(value);
			case Value::Type::MAP:           return this->mark_map(value);
			case Value::Type::RNG:           return this->mark_rng(value);
			case Value::Type::TYPE:          return; // no gc required
		}
	}



	void Heap::mark_array(const Value & ref) {
		auto & pool = pool_of<Array>(); 
		if(!pool.gc_is_marked(ref.u)) {
			pool.gc_mark(ref.u);
			auto & arr = pool.get(ref.u);
			this->mark(arr);
		}
	}



	void Heap::mark_string(const Value & value) {
		pool_of<String>().gc_mark(value.u);
	}



	void Heap::mark_istream(const Value & value) {
		pool_of<IStream>().gc_mark(value.u);
	}



	void Heap::mark_iterator(const Value & value) {
		auto & pool = pool_of<Iterator>(); 
		if(!pool.gc_is_marked(value.u)) {
			pool.gc_mark(value.u);
			auto & iter = pool.get(value.u);
			iter.mark(*this);
		}
	}



	void Heap::mark_ostream(const Value & value) {
		pool_of<OStream>().gc_mark(value.u);
	}



	void Heap::mark_fxptr(const Value & ref) {
		auto & pool = pool_of<FxPointer>(); 
		if(!pool.gc_is_marked(ref.u)) {
			pool.gc_mark(ref.u);
			auto & fx = pool.get(ref.u);
			this->mark(fx.captured);
		}
	}



	void Heap::mark_struct(const Value & ref) {
		auto & pool = pool_of<Struct>(); 
		if(!pool.gc_is_marked(ref.u)) {
			pool.gc_mark(ref.u);
			auto & s = pool.get(ref.u);
			for(const auto & [key, value] : s.members) {
				this->mark(value);
			}
		}
	}



	void Heap::mark_deque(const Value & ref) {
		auto & pool = pool_of<Deque>(); 
		if(!pool.gc_is_marked(ref.u)) {
			pool.gc_mark(ref.u);
			auto & deq = pool.get(ref.u);
			this->mark(deq);
		}
	}



	void Heap::mark_map(const Value & value) {
		auto & pool = pool_of<Map>(); 
		if(!pool.gc_is_marked(value.u)) {
			pool.gc_mark(value.u);
			auto & map = pool.get(value.u);
			for(auto & [key, value] : map) {
				this->mark(key);
				this->mark(value);
			}
		}
	}



	void Heap::mark_clock(const Value & value) {
		pool_of<Clock>().gc_mark(value.u);
	}



	void Heap::mark_rng(const Value & value) {
		pool_of<RandomEngine>().gc_mark(value.u);
	}



	void Heap::sweep() {
		pool_of<String>().gc_sweep();
		pool_of<Array>().gc_sweep();
		pool_of<IStream>().gc_sweep();
		pool_of<Iterator>().gc_sweep();
		pool_of<OStream>().gc_sweep();
		pool_of<FxPointer>().gc_sweep();
		pool_of<Clock>().gc_sweep();
		pool_of<Struct>().gc_sweep();
		pool_of<Deque>().gc_sweep();
		pool_of<Map>().gc_sweep();
		pool_of<RandomEngine>().gc_sweep();
	}
}