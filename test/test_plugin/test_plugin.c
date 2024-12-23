#include <stdio.h>

#define LTN_IMPL
#include "native/litan.h"

#include "is_type.h"
#include "as_type.h"


ltn_Value test(ltn_Context * context, const ltn_Value* args) {
	ltn_Array test_array = ltn_alloc_array(context,0,0);
	ltn_array_push(test_array, ltn_value_int(1));
	ltn_array_push(test_array, ltn_value_int(2));
	ltn_array_push(test_array, ltn_value_int(3));
	for(int i = 0; i < 10000; i++) {
		ltn_alloc_string(context,"");
	}
	return ltn_value_array(test_array);
}




extern ltn_NativeFunctionInfo ltn_exports[];
ltn_NativeFunctionInfo ltn_exports[] = {
	{ "test_1",    test,           0, ltn_DEFAULT },
	{ "test_2",    test,           0, ltn_USE_GC  },

	{ "is_null",   test_is_null,   1, ltn_DEFAULT },
	{ "is_bool",   test_is_bool,   1, ltn_DEFAULT },
	{ "is_int",    test_is_int,    1, ltn_DEFAULT },
	{ "is_float",  test_is_float,  1, ltn_DEFAULT },
	{ "is_array",  test_is_array,  1, ltn_DEFAULT },
	{ "is_tuple",  test_is_tuple,  1, ltn_DEFAULT },
	{ "is_string", test_is_string, 1, ltn_DEFAULT },
	{ "is_map",    test_is_map,    1, ltn_DEFAULT },

	{ "as_bool",   test_as_bool,   1, ltn_DEFAULT },
	{ "as_int",    test_as_int,    1, ltn_DEFAULT },
	{ "as_float",  test_as_float,  1, ltn_DEFAULT },
	{ "as_array",  test_as_array,  1, ltn_DEFAULT },
	{ "as_tuple",  test_as_tuple,  1, ltn_DEFAULT },
	{ "as_string", test_as_string, 1, ltn_DEFAULT },
	{ "as_map",    test_as_map,    1, ltn_DEFAULT },

	{ 0, 0, 0, 0}
};



void init() {}
void gc_mark() {}


extern ltn_PluginInfo ltn_plugin_info;
ltn_PluginInfo ltn_plugin_info = {
	.init = init,
	.gc_mark = gc_mark,
};
