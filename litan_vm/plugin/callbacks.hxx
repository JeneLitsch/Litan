#pragma once

#include "litan_native/litan.h"

namespace ltn::vm::plugin::callback {
	void gc_mark(ltn_Value value);

	ltn_Array alloc_array(ltn_Context * mative_core, const ltn_Value * data, uint64_t size);
	ltn_Tuple alloc_tuple(ltn_Context * mative_core, const ltn_Value * data, uint64_t size);
	ltn_Map alloc_map(ltn_Context * mative_core, const ltn_Value * key_data, const ltn_Value * value_data, uint64_t size);
	ltn_String alloc_string(ltn_Context * mative_core, const char * data);



	ltn_Value value_null();
	ltn_Value value_bool(ltn_Bool boolean);
	ltn_Value value_int(ltn_Int integer);
	ltn_Value value_float(ltn_Float floating);
	ltn_Value value_array(ltn_Array array);
	ltn_Value value_tuple(ltn_Tuple tuple);
	ltn_Value value_map(ltn_Map map);
	ltn_Value value_string(ltn_String string);



	ltn_Bool as_bool(ltn_Value value);
	ltn_Int as_int(ltn_Value value);
	ltn_Float as_float(ltn_Value value);
	ltn_Array as_array(ltn_Value value);
	ltn_Tuple as_tuple(ltn_Value value);
	ltn_Map as_map(ltn_Value value);
	ltn_String as_string(ltn_Value value);



	ltn_Bool is_null(ltn_Value value);
	ltn_Bool is_bool(ltn_Value value);
	ltn_Bool is_int(ltn_Value value);
	ltn_Bool is_float(ltn_Value value);
	ltn_Bool is_array(ltn_Value value);
	ltn_Bool is_tuple(ltn_Value value);
	ltn_Bool is_map(ltn_Value value);
	ltn_Bool is_string(ltn_Value value);



	ltn_Value array_at(ltn_Array array, ltn_Int i);
	void array_put(ltn_Array array, ltn_Int i, ltn_Value value);
	ltn_Int array_size(ltn_Array array);
	void array_push(ltn_Array array, ltn_Value value);
	ltn_Value array_pop(ltn_Array array);
	void array_insert(ltn_Array array, ltn_Int i, ltn_Value value);
	ltn_Value array_erase(ltn_Array array, ltn_Int i);



	const char * string_data(ltn_String string);
	int64_t string_size(ltn_String string);



	ltn_Value map_at(ltn_Map map, ltn_Value key);
	void map_put(ltn_Map map, ltn_Value key, ltn_Value value);
	ltn_Int map_size(ltn_Map map);
	ltn_Bool map_has(ltn_Map map, ltn_Value key);



	ltn_Value tuple_at(ltn_Tuple tuple, ltn_Int index);
	ltn_Int tuple_size(ltn_Tuple tuple);
}