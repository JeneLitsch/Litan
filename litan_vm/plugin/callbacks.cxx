#include "callbacks.hxx"
#include "litan_vm/VMCore.hxx"

namespace ltn::vm::plugin::callback {
	void gc_mark(Value value) {
		gc::mark(value);
	}



	ltn_Array alloc_array(Context * mative_core, const Value * data, uint64_t size) {
		VMCore * core = static_cast<VMCore*>(mative_core->core); 
		core->heap.collect_garbage(core->stack);
		Array * array = core->heap.alloc<Array>(Array());
		if (data) {
			for(std::size_t i = 0; i < size; i++) {
				array->push_back(data[i]);
			}
		}
		return ltn_Array{.ptr = static_cast<void*>(array)};
	}



	ltn_Tuple alloc_tuple(Context * mative_core, const Value * data, uint64_t size) {
		VMCore * core = static_cast<VMCore*>(mative_core->core); 
		core->heap.collect_garbage(core->stack);
		Tuple * tuple = core->heap.make<Tuple>();
		if (data) {
			for(std::size_t i = 0; i < size; i++) {
				tuple->push_back(data[i]);
			}
		}
		return ltn_Tuple{.ptr = static_cast<void*>(tuple)};
	}


	
	ltn_Map alloc_map(Context * mative_core, const Value * key_data, const Value * value_data, uint64_t size) {
		VMCore * core = static_cast<VMCore*>(mative_core->core); 
		core->heap.collect_garbage(core->stack);
		Map * map = core->heap.alloc<Map>(Map(core));
		Map::std_map & std_map = map->get_underlying();
		for(std::size_t i = 0; i < size; i++) {
			std_map[key_data[i]] = value_data[i];
		}
		return ltn_Map{.ptr = static_cast<void*>(map)};
	}



	ltn_String alloc_string(Context * mative_core, const char * data) {
		VMCore * core = static_cast<VMCore*>(mative_core->core); 
		core->heap.collect_garbage(core->stack);
		String * string = core->heap.alloc<String>(std::string{data});
		return ltn_String{.ptr = static_cast<void*>(string)};
	}



	ltn_Value value_null() {
		return value::null;
	}



	ltn_Value value_bool(ltn_Bool boolean) {
		return value::boolean(boolean);
	}



	ltn_Value value_int(ltn_Int integer) {
		return value::integer(integer);
	}



	ltn_Value value_float(ltn_Float floating) {
		return value::floating(floating);
	}



	Value value_array(ltn_Array array) {
		return value::array(static_cast<Array*>(array.ptr));
	}
	


	Value value_tuple(ltn_Tuple array) {
		return value::tuple(static_cast<Tuple*>(array.ptr));
	}
	


	Value value_map(ltn_Map array) {
		return value::map(static_cast<Map*>(array.ptr));
	}



	Value value_string(ltn_String string) {
		return value::string(static_cast<String*>(string.ptr));
	}



	ltn_Bool as_bool(Value value) {
		if (!is_bool(value)) {
			throw except::invalid_argument();
		}
		return value.b;
	}



	ltn_Int as_int(Value value) {
		if (!is_int(value)) {
			throw except::invalid_argument();
		}
		return value.i;
	}



	ltn_Float as_float(Value value) {
		if (!is_float(value)) {
			throw except::invalid_argument();
		}
		return value.f;
	}



	ltn_Array as_array(Value value) {
		if (!is_array(value)) {
			throw except::invalid_argument();
		}
		return ltn_Array{ .ptr = value.object };
	}



	ltn_Tuple as_tuple(Value value) {
		if (!is_tuple(value)) {
			throw except::invalid_argument();
		}
		return ltn_Tuple{ .ptr = value.object };
	}



	ltn_Map as_map(Value value) {
		if (!is_map(value)) {
			throw except::invalid_argument();
		}
		return ltn_Map{ .ptr = value.object };
	}
	


	ltn_String as_string(Value value) {
		if (!is_string(value)) {
			throw except::invalid_argument();
		}
		return ltn_String{ .ptr = value.object };
	}



	ltn_Bool is_null(ltn_Value value) {
		return ltn::vm::is_null(value);
	}



	ltn_Bool is_bool(ltn_Value value) {
		return ltn::vm::is_bool(value);
	}



	ltn_Bool is_int(ltn_Value value) {
		return ltn::vm::is_int(value);
	}



	ltn_Bool is_float(ltn_Value value) {
		return ltn::vm::is_float(value);
	}



	ltn_Bool is_array(ltn_Value value) {
		return ltn::vm::is_array(value);
	}



	ltn_Bool is_tuple(ltn_Value value) {
		return ltn::vm::is_tuple(value);
	}



	ltn_Bool is_map(ltn_Value value) {
		return ltn::vm::is_map(value);
	}



	ltn_Bool is_string(ltn_Value value) {
		return ltn::vm::is_string(value);
	}



	Value array_at(ltn_Array array, int64_t i) {
		return static_cast<Array*>(array.ptr)->at(i);
	}



	void array_put(ltn_Array array, int64_t i, Value value) {
		static_cast<Array*>(array.ptr)->at(i) = value;
	}



	int64_t array_size(ltn_Array array) {
		return static_cast<std::int64_t>(static_cast<Array*>(array.ptr)->size());
	}



	void array_push(ltn_Array array, Value value) {
		return static_cast<Array*>(array.ptr)->push_back(value);
	}



	Value array_pop(ltn_Array array) {
		return static_cast<Array*>(array.ptr)->pop_back();
	}



	void array_insert(ltn_Array array, std::int64_t i, Value value) {
		return static_cast<Array*>(array.ptr)->insert(i, value);
	}



	Value array_erase(ltn_Array array, std::int64_t i) {
		return static_cast<Array*>(array.ptr)->erase(i);
	}



	const char * string_data(ltn_String string) {
		String * str = static_cast<String*>(string.ptr);
		std::string_view view = *str;
		return view.data();
	}



	int64_t string_size(ltn_String string) {
		return static_cast<String*>(string.ptr)->size();
	}



	Value map_at(ltn_Map map, Value key) {
		return static_cast<Map*>(map.ptr)->at(key);
	}



	void map_put(ltn_Map map, Value key, Value value) {
		static_cast<Map*>(map.ptr)->get_underlying()[key] = value;
	}



	int64_t map_size(ltn_Map map) {
		return static_cast<std::int64_t>(static_cast<Map*>(map.ptr)->size());
	}



	bool map_has(ltn_Map map, Value key) {
		return static_cast<Map*>(map.ptr)->contains(key);
	}



	Value tuple_at(ltn_Tuple tuple, ltn_Int index) {
		Tuple * t = static_cast<Tuple*>(tuple.ptr);
		if(std::ssize(*t) <= index) {
			throw except::out_of_range();
		}
		return t->unsafe_at(index);
	}



	int64_t tuple_size(ltn_Tuple tuple) {
		return static_cast<std::int64_t>(static_cast<Tuple*>(tuple.ptr)->size());
	}
}