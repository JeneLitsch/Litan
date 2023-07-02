#include "gc.hxx"

namespace ltn::vm::gc {
	void mark_array(Array * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->data);
		}
	}



	void mark_string(String * obj) {
		obj->marked = true;
	}



	void mark_istream(IStream * obj) {
		obj->marked = true;
	}



	void mark_iterator(Iterator * obj) {
		if(!obj->marked) {
			obj->marked = true;
			obj->mark();
		}
	}



	void mark_ostream(OStream * obj) {
		obj->marked = true;
	}



	void mark_fxptr(FxPointer * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->captured);
		}
	}



	void mark_struct(Struct * obj) {
		if(!obj->marked) {
			obj->marked = true;
			for(const auto & [key, value] : obj->members) {
				mark(value);
			}
		}
	}



	void mark_deque(Deque * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->data);
		}
	}



	void mark_map(Map * obj) {
		if(!obj->marked) {
			obj->marked = true;
			for(auto & [key, value] : *obj) {
				mark(key);
				mark(value);
			}
		}
	}



	void mark_clock(Clock * obj) {
		obj->marked = true;
	}



	void mark_rng(RandomEngine * obj) {
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
		using VT = Value::Type; 
		switch (value.type) {
			case VT::NVLL:          return; // no gc required
			case VT::BOOL:          return; // no gc required
			case VT::INT:           return; // no gc required
			case VT::FLOAT:         return; // no gc required
			case VT::CHAR:          return; // no gc required
			case VT::ARRAY:         return mark_array(value.as<Array>());
			case VT::STRING:        return mark_string(value.as<String>());
			case VT::TUPLE:         return mark_array(value.as<Array>());
			case VT::ISTREAM:       return mark_istream(value.as<IStream>());
			case VT::ITERATOR:      return mark_iterator(value.as<Iterator>());
			case VT::ITERATOR_STOP: return; // no gc required
			case VT::OSTREAM:       return mark_ostream(value.as<OStream>());
			case VT::FX_PTR:        return mark_fxptr(value.as<FxPointer>());
			case VT::CLOCK:         return mark_clock(value.as<Clock>());
			case VT::STRUCT:        return mark_struct(value.as<Struct>());
			case VT::QUEUE:         return mark_deque(value.as<Deque>());
			case VT::STACK:         return mark_deque(value.as<Deque>());
			case VT::MAP:           return mark_map(value.as<Map>());
			case VT::RNG:           return mark_rng(value.as<RandomEngine>());
			case VT::TYPE:          return; // no gc required
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