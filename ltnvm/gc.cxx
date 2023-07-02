#include "gc.hxx"

namespace ltn::vm::gc {
	void mark_array(const Value & value) {
		auto * obj = value.as<Array>();
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->data);
		}
	}



	void mark_string(const Value & value) {
		auto * obj = value.as<String>();
		obj->marked = true;
	}



	void mark_istream(const Value & value) {
		auto * obj = value.as<IStream>();
		obj->marked = true;
	}



	void mark_iterator(const Value & value) {
		auto * obj = value.as<Iterator>();
		if(!obj->marked) {
			obj->marked = true;
			obj->mark();
		}
	}



	void mark_ostream(const Value & value) {
		auto * obj = value.as<OStream>();
		obj->marked = true;
	}



	void mark_fxptr(const Value & value) {
		auto * obj = value.as<FxPointer>();
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->captured);
		}
	}



	void mark_struct(const Value & value) {
		auto * obj = value.as<Struct>();
		if(!obj->marked) {
			obj->marked = true;
			for(const auto & [key, value] : obj->members) {
				mark(value);
			}
		}
	}



	void mark_deque(const Value & value) {
		auto * obj = value.as<Deque>();
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->data);
		}
	}



	void mark_map(const Value & value) {
		auto * obj = value.as<Map>();
		if(!obj->marked) {
			obj->marked = true;
			for(auto & [key, value] : *obj) {
				mark(key);
				mark(value);
			}
		}
	}



	void mark_clock(const Value & value) {
		auto * obj = value.as<Clock>();
		obj->marked = true;
	}



	void mark_rng(const Value & value) {
		auto * obj = value.as<RandomEngine>();
		obj->marked = true;
	}



	void mark(const std::vector<Value> & values) {
		for(const auto & value : values) {
			mark(value);
		}
	}



	void mark(const std::deque<Value> & values) {
		for(const auto & value : values) {
			mark(value);
		}
	}



	void mark(const Value & value) {
		switch (value.type) {
			case Value::Type::NVLL:          return; // no gc required
			case Value::Type::BOOL:          return; // no gc required
			case Value::Type::INT:           return; // no gc required
			case Value::Type::FLOAT:         return; // no gc required
			case Value::Type::CHAR:          return; // no gc required
			case Value::Type::ARRAY:         return mark_array(value);
			case Value::Type::STRING:        return mark_string(value);
			case Value::Type::TUPLE:         return mark_array(value);
			case Value::Type::ISTREAM:       return mark_istream(value);
			case Value::Type::ITERATOR:      return mark_iterator(value);
			case Value::Type::ITERATOR_STOP: return; // no gc required
			case Value::Type::OSTREAM:       return mark_ostream(value);
			case Value::Type::FX_PTR:        return mark_fxptr(value);
			case Value::Type::CLOCK:         return mark_clock(value);
			case Value::Type::STRUCT:        return mark_struct(value);
			case Value::Type::QUEUE:         return mark_deque(value);
			case Value::Type::STACK:         return mark_deque(value);
			case Value::Type::MAP:           return mark_map(value);
			case Value::Type::RNG:           return mark_rng(value);
			case Value::Type::TYPE:          return; // no gc required
		}
	}



	std::uint64_t sweep(std::unique_ptr<Object> & start) {
		std::unique_ptr<Object> * current = &start;
		std::uint64_t collected = 0;
		while (*current) {
			if((*current)->marked) {
				(*current)->marked = false;
				current = &(*current)->next_object;
			}
			else {
				++collected;
				*current = std::move((*current)->next_object);
			}
		}
		return collected;
	}
}