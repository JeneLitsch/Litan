#include "is_type.h"

ltn_Value test_is_null(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_is_null(args[0]));
}



ltn_Value test_is_bool(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_is_bool(args[0]));
}



ltn_Value test_is_int(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_is_int(args[0]));
}



ltn_Value test_is_float(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_is_float(args[0]));
}



ltn_Value test_is_array(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_is_array(args[0]));
}



ltn_Value test_is_tuple(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_is_tuple(args[0]));
}



ltn_Value test_is_string(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_is_string(args[0]));
}



ltn_Value test_is_map(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_is_map(args[0]));
}
