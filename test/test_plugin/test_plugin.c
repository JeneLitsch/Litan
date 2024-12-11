#include <stdio.h>

#define LTN_IMPL
#include "native/litan.h"

#include "is_type.h"
#include "as_type.h"

ltn_Array test_array;

ltn_Value test_1(ltn_Context * context, const ltn_Value* args) {
	test_array = ltn_alloc_array(context,0,0);
	for(int i = 0; i < 1000000; i++) {
		ltn_alloc_array(context,0,0);
	}
	return ltn_value_array(test_array);
}



ltn_Value test_2(ltn_Context * context, const ltn_Value* args) {
	return ltn_value_array(test_array);
}



extern ltn_NativeFunctionInfo ltn_exports[] = {
	{ "test_1", test_1, 0 },
	{ "test_2", test_2, 0 },

	{ "is_null", test_is_null, 1 },
	{ "is_bool", test_is_bool, 1 },
	{ "is_char", test_is_char, 1 },
	{ "is_int", test_is_int, 1 },
	{ "is_float", test_is_float, 1 },
	{ "is_array", test_is_array, 1 },
	{ "is_tuple", test_is_tuple, 1 },
	{ "is_string", test_is_string, 1 },
	{ "is_map", test_is_map, 1 },

	{ "as_bool", test_as_bool, 1 },
	{ "as_char", test_as_char, 1 },
	{ "as_int", test_as_int, 1 },
	{ "as_float", test_as_float, 1 },
	{ "as_array", test_as_array, 1 },
	{ "as_tuple", test_as_tuple, 1 },
	{ "as_string", test_as_string, 1 },
	{ "as_map", test_as_map, 1 },

	{0,0,0}
};



void init() {}
void gc_mark() {
	// printf("GC\n");
	ltn_gc_mark(ltn_value_array(test_array));
}


extern ltn_PluginInfo ltn_plugin_info = {
	.init = init,
	.gc_mark = gc_mark,
};
