#include "gc.hxx"

namespace ltn::vm::gc {
	void mark_obj(Array * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->data);
		}
	}



	void mark_obj(String * obj) {
		obj->marked = true;
	}



	void mark_obj(IStream * obj) {
		obj->marked = true;
	}



	void mark_obj(Iterator * obj) {
		if(!obj->marked) {
			obj->marked = true;
			obj->mark();
		}
	}



	void mark_obj(OStream * obj) {
		obj->marked = true;
	}



	void mark_obj(FxPointer * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->captured);
		}
	}



	void mark_obj(Struct * obj) {
		if(!obj->marked) {
			obj->marked = true;
			for(const auto & [key, value] : obj->members) {
				mark(value);
			}
		}
	}



	void mark_obj(Deque * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->data);
		}
	}



	void mark_obj(Map * obj) {
		if(!obj->marked) {
			obj->marked = true;
			for(auto & [key, value] : *obj) {
				mark(key);
				mark(value);
			}
		}
	}



	void mark_obj(Clock * obj) {
		obj->marked = true;
	}



	void mark_obj(RandomEngine * obj) {
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
			case VT::ARRAY:         return mark_obj(value.as<Array>());
			case VT::STRING:        return mark_obj(value.as<String>());
			case VT::TUPLE:         return mark_obj(value.as<Array>());
			case VT::ISTREAM:       return mark_obj(value.as<IStream>());
			case VT::ITERATOR:      return mark_obj(value.as<Iterator>());
			case VT::ITERATOR_STOP: return; // no gc required
			case VT::OSTREAM:       return mark_obj(value.as<OStream>());
			case VT::FX_PTR:        return mark_obj(value.as<FxPointer>());
			case VT::CLOCK:         return mark_obj(value.as<Clock>());
			case VT::STRUCT:        return mark_obj(value.as<Struct>());
			case VT::QUEUE:         return mark_obj(value.as<Deque>());
			case VT::STACK:         return mark_obj(value.as<Deque>());
			case VT::MAP:           return mark_obj(value.as<Map>());
			case VT::RNG:           return mark_obj(value.as<RandomEngine>());
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