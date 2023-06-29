#include "Heap.hxx"
#include "ltnvm/utils/type_check.hxx"
namespace ltn::vm {
	void Heap::mark(const std::vector<Value> & values) {
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



	void Heap::mark_array(const Value & value) {
		auto * obj = value.as<Array>();
		if(!obj->marked) {
			obj->marked = true;
			this->mark(obj->data);
		}
	}



	void Heap::mark_string(const Value & value) {
		auto * obj = value.as<String>();
		obj->marked = true;
	}



	void Heap::mark_istream(const Value & value) {
		auto * obj = value.as<IStream>();
		obj->marked = true;
	}



	void Heap::mark_iterator(const Value & value) {
		auto * obj = value.as<Iterator>();
		if(!obj->marked) {
			obj->marked = true;
			obj->mark(*this);
		}
	}



	void Heap::mark_ostream(const Value & value) {
		auto * obj = value.as<OStream>();
		obj->marked = true;
	}



	void Heap::mark_fxptr(const Value & value) {
		auto * obj = value.as<FxPointer>();
		if(!obj->marked) {
			obj->marked = true;
			this->mark(obj->captured);
		}
	}



	void Heap::mark_struct(const Value & value) {
		auto * obj = value.as<Struct>();
		if(!obj->marked) {
			obj->marked = true;
			for(const auto & [key, value] : obj->members) {
				this->mark(value);
			}
		}
	}



	void Heap::mark_deque(const Value & value) {
		auto * obj = value.as<Deque>();
		if(!obj->marked) {
			obj->marked = true;
			this->mark(obj->data);
		}
	}



	void Heap::mark_map(const Value & value) {
		auto * obj = value.as<Map>();
		if(!obj->marked) {
			obj->marked = true;
			for(auto & [key, value] : *obj) {
				this->mark(key);
				this->mark(value);
			}
		}
	}



	void Heap::mark_clock(const Value & value) {
		auto * obj = value.as<Clock>();
		obj->marked = true;
	}



	void Heap::mark_rng(const Value & value) {
		auto * obj = value.as<RandomEngine>();
		obj->marked = true;
	}



	void Heap::sweep() {
		std::unique_ptr<Object> * current = &this->objects;
		while (*current) {
			if((*current)->marked) {
				(*current)->marked = false;
				current = &(*current)->next_object;
			}
			else {
				// current = &(*current)->next_object;
				*current = std::move((*current)->next_object);
			}
		}
	}
}