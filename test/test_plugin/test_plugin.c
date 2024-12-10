#include <stdio.h>

#define LTN_IMPL
#include "native/litan.h"

#include "is_type.h"

ltn_Value test(ltn_Context * ctx, const ltn_Value * args) {
	ltn_String str = ltn_alloc_string(ctx, "Hello World!");
	ltn_Value data[7] = {
		ltn_value_bool(true),
		ltn_value_int(42),
		ltn_value_float(13.37),
		ltn_value_string(str),
		ltn_value_null(),
		ltn_value_bool(ltn_is_null(ltn_value_null())),
		ltn_value_bool(ltn_is_null(ltn_value_int(1))),
	};
	ltn_Array array = ltn_alloc_array(ctx, data, 7);
	return ltn_value_array(array);
}



ltn_Value add(ltn_Context * ctx, const ltn_Value * args) {
	return ltn_value_bool(ltn_is_int(args[0]));
}



ltn_Value sum(ltn_Context * ctx, const ltn_Value * args) {
	ltn_Array array = ltn_as_array(args[0]);
	int64_t value;
	for(int i = 0; i < ltn_array_size(array); i++) {
		ltn_Value elem = ltn_array_at(array, i);
		value += ltn_as_int(elem);
	}
	return ltn_value_int(value);
}



ltn_Value array_operations(ltn_Context * ctx, const ltn_Value * args) {
	ltn_Array array = ltn_alloc_array(ctx, 0, 0);
	ltn_array_push(array, ltn_value_int(42));
	ltn_array_push(array, ltn_value_bool(false));
	ltn_Value v = ltn_array_pop(array);
	ltn_array_push(array, v);
	ltn_array_push(array, v);
	ltn_array_put(array, 0, ltn_value_int(1337));
	ltn_array_insert(array, 0, ltn_value_char('A'));
	ltn_array_erase(array, 2);
	return ltn_value_array(array);
}



ltn_Value test_string(ltn_Context * context, const ltn_Value * args) {
	ltn_String string = ltn_as_string(args[0]);
	printf("%s\n", ltn_string_data(string));
	return ltn_value_int(ltn_string_size(string));
}



ltn_Value test_map(ltn_Context * context, const ltn_Value * args) {
	ltn_Map map = ltn_alloc_map(context, 0, 0, 0);
	ltn_map_put(map, ltn_value_int(1), ltn_value_int(11));
	ltn_map_put(map, ltn_value_int(2), ltn_value_int(22));
	ltn_map_put(map, ltn_value_bool(true), ltn_value_int(ltn_map_size(map)));
	return ltn_value_map(map);
}


ltn_Value test_tuple(ltn_Context * context, const ltn_Value * args) {
	ltn_Tuple tuple = ltn_as_tuple(args[0]);
	ltn_Int a = ltn_as_int(ltn_tuple_at(tuple, 0));
	ltn_Int b = ltn_as_int(ltn_tuple_at(tuple, 1));
	ltn_Value tuple_values[3] = {
		ltn_value_int(a + b),
		ltn_value_bool(ltn_is_tuple(args[0])),
		ltn_value_bool(ltn_is_tuple(ltn_value_int(42))),
	};
	ltn_Tuple new_tuple = ltn_alloc_tuple(context, tuple_values, 3);
	return ltn_value_tuple(new_tuple);
}



extern ltn_NativeFunctionInfo ltn_exports[] = {
	{ "test", test, 0 },
	{ "add", add, 2 },
	{ "sum", sum, 1 },
	{ "array_operations", array_operations, 0 },
	{ "test_string", test_string, 1 },
	{ "test_map", test_map, 0 },
	{ "test_tuple", test_tuple, 1 },

	{ "is_null", test_is_null, 1 },
	{ "is_bool", test_is_bool, 1 },
	{ "is_char", test_is_char, 1 },
	{ "is_int", test_is_int, 1 },
	{ "is_float", test_is_float, 1 },

	{0,0,0}
};



void init() {}

extern ltn_PluginInfo ltn_plugin_info = {
	.init = init,
};
