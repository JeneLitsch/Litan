#include "Heap.hxx"
#include "stdxx/oop.hxx"
#include "ltnvm/utils/type_check.hxx"
namespace ltn::vm {
	void do_mark_array(const Value & value) {
		auto * obj = value.as<Array>();
		if(!obj->marked) {
			obj->marked = true;
			do_mark(obj->data);
		}
	}



	void do_mark_string(const Value & value) {
		auto * obj = value.as<String>();
		obj->marked = true;
	}



	void do_mark_istream(const Value & value) {
		auto * obj = value.as<IStream>();
		obj->marked = true;
	}



	void do_mark_iterator(const Value & value) {
		auto * obj = value.as<Iterator>();
		if(!obj->marked) {
			obj->marked = true;
			obj->mark();
		}
	}



	void do_mark_ostream(const Value & value) {
		auto * obj = value.as<OStream>();
		obj->marked = true;
	}



	void do_mark_fxptr(const Value & value) {
		auto * obj = value.as<FxPointer>();
		if(!obj->marked) {
			obj->marked = true;
			do_mark(obj->captured);
		}
	}



	void do_mark_struct(const Value & value) {
		auto * obj = value.as<Struct>();
		if(!obj->marked) {
			obj->marked = true;
			for(const auto & [key, value] : obj->members) {
				do_mark(value);
			}
		}
	}



	void do_mark_deque(const Value & value) {
		auto * obj = value.as<Deque>();
		if(!obj->marked) {
			obj->marked = true;
			do_mark(obj->data);
		}
	}



	void do_mark_map(const Value & value) {
		auto * obj = value.as<Map>();
		if(!obj->marked) {
			obj->marked = true;
			for(auto & [key, value] : *obj) {
				do_mark(key);
				do_mark(value);
			}
		}
	}



	void do_mark_clock(const Value & value) {
		auto * obj = value.as<Clock>();
		obj->marked = true;
	}



	void do_mark_rng(const Value & value) {
		auto * obj = value.as<RandomEngine>();
		obj->marked = true;
	}



	void do_mark(const std::vector<Value> & values) {
		for(const auto & value : values) {
			do_mark(value);
		}
	}



	void do_mark(const std::deque<Value> & values) {
		for(const auto & value : values) {
			do_mark(value);
		}
	}



	void do_mark(const Value & value) {
		switch (value.type) {
			case Value::Type::NVLL:          return; // no gc required
			case Value::Type::BOOL:          return; // no gc required
			case Value::Type::INT:           return; // no gc required
			case Value::Type::FLOAT:         return; // no gc required
			case Value::Type::CHAR:          return; // no gc required
			case Value::Type::ARRAY:         return do_mark_array(value);
			case Value::Type::STRING:        return do_mark_string(value);
			case Value::Type::TUPLE:         return do_mark_array(value);
			case Value::Type::ISTREAM:       return do_mark_istream(value);
			case Value::Type::ITERATOR:      return do_mark_iterator(value);
			case Value::Type::ITERATOR_STOP: return; // no gc required
			case Value::Type::OSTREAM:       return do_mark_ostream(value);
			case Value::Type::FX_PTR:        return do_mark_fxptr(value);
			case Value::Type::CLOCK:         return do_mark_clock(value);
			case Value::Type::STRUCT:        return do_mark_struct(value);
			case Value::Type::QUEUE:         return do_mark_deque(value);
			case Value::Type::STACK:         return do_mark_deque(value);
			case Value::Type::MAP:           return do_mark_map(value);
			case Value::Type::RNG:           return do_mark_rng(value);
			case Value::Type::TYPE:          return; // no gc required
		}
	}



	void Heap::mark(const std::vector<Value> & values) {
		return do_mark(values);
	}



	void Heap::mark(const std::deque<Value> & values) {
		return do_mark(values);
	}



	void Heap::mark(const Value & value) {
		return do_mark(value);
	}



	void Heap::sweep() {
		std::unique_ptr<Object> * current = &this->objects;
		while (*current) {
			if((*current)->marked) {
				(*current)->marked = false;
				current = &(*current)->next_object;
			}
			else {
				--this->size;
				*current = std::move((*current)->next_object);
			}
		}
	}
}