#include "as_type.h"



ltn_Value test_as_bool(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_bool(ltn_as_bool(args[0]));
}



ltn_Value test_as_int(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_int(ltn_as_int(args[0]));
}



ltn_Value test_as_float(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_float(ltn_as_float(args[0]));
}



ltn_Value test_as_array(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_array(ltn_as_array(args[0]));
}



ltn_Value test_as_tuple(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_tuple(ltn_as_tuple(args[0]));
}



ltn_Value test_as_string(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_string(ltn_as_string(args[0]));
}



ltn_Value test_as_map(ltn_Context * context, const ltn_Value * args) {
	(void)context;
	return ltn_value_map(ltn_as_map(args[0]));
}
