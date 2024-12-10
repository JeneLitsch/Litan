#include "is_type.h"

ltn_Value test_is_null(ltn_Context * context, const ltn_Value * args) {
	return ltn_value_bool(ltn_is_null(args[0]));
}



ltn_Value test_is_bool(ltn_Context * context, const ltn_Value * args) {
	return ltn_value_bool(ltn_is_bool(args[0]));
}



ltn_Value test_is_char(ltn_Context * context, const ltn_Value * args) {
	return ltn_value_bool(ltn_is_char(args[0]));
}



ltn_Value test_is_int(ltn_Context * context, const ltn_Value * args) {
	return ltn_value_bool(ltn_is_int(args[0]));
}



ltn_Value test_is_float(ltn_Context * context, const ltn_Value * args) {
	return ltn_value_bool(ltn_is_float(args[0]));
}