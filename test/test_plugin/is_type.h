#pragma once
#include "native/litan.h"


// Primitive types
ltn_Value test_is_null(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_bool(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_char(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_int(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_float(ltn_Context * context, const ltn_Value * args);

// Object types
ltn_Value test_is_array(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_tuple(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_string(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_map(ltn_Context * context, const ltn_Value * args);