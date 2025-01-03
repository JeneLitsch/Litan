#include "gc.hxx"

namespace ltn::vm::gc {
	void mark_obj(Contiguous * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->get_underlying());
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



	void mark_obj(ScriptFunctionPointer * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->captured);
		}
	}


	void mark_obj(NativeFunctionPointer * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->captured);
			mark_obj(obj->plugin);
		}
	}



	void mark_obj(Plugin * obj) {
		if(!obj->marked) {
			obj->marked = true;
			obj->gc_mark();
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



	void mark_obj(Segmented * obj) {
		if(!obj->marked) {
			obj->marked = true;
			mark(obj->get_underlying());
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



	void mark_obj(Coroutine * obj) {
		mark(obj->local_variables);		
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
		using VT = ValueType; 
		switch (static_cast<VT>(value.type)) {
			case VT::NVLL:            return; // no gc required
			case VT::BOOL:            return; // no gc required
			case VT::INT:             return; // no gc required
			case VT::FLOAT:           return; // no gc required
			case VT::ARRAY:           return mark_obj(value::as<Array>(value));
			case VT::STRING:          return mark_obj(value::as<String>(value));
			case VT::TUPLE:           return mark_obj(value::as<Tuple>(value));
			case VT::ISTREAM:         return mark_obj(value::as<IStream>(value));
			case VT::ITERATOR:        return mark_obj(value::as<Iterator>(value));
			case VT::ITERATOR_STOP:   return; // no gc required
			case VT::OSTREAM:         return mark_obj(value::as<OStream>(value));
			case VT::FUNCTION:        return mark_obj(value::as<ScriptFunctionPointer>(value));
			case VT::NATIVE_FUNCTION: return mark_obj(value::as<NativeFunctionPointer>(value));
			case VT::CLOCK:           return mark_obj(value::as<Clock>(value));
			case VT::STRUCT:          return mark_obj(value::as<Struct>(value));
			case VT::QUEUE:           return mark_obj(value::as<Segmented>(value));
			case VT::STACK:           return mark_obj(value::as<Segmented>(value));
			case VT::MAP:             return mark_obj(value::as<Map>(value));
			case VT::RNG:             return mark_obj(value::as<RandomEngine>(value));
			case VT::COROUTINE:       return mark_obj(value::as<Coroutine>(value));
		}
	}



	std::uint64_t sweep(std::unique_ptr<Object> & start) {
		// return 0;
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