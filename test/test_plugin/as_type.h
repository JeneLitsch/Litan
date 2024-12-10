#pragma once

#include "native/litan.h"

// Primitive types
ltn_Value test_as_bool(ltn_Context * context, const ltn_Value * args);
ltn_Value test_as_char(ltn_Context * context, const ltn_Value * args);
ltn_Value test_as_int(ltn_Context * context, const ltn_Value * args);
ltn_Value test_as_float(ltn_Context * context, const ltn_Value * args);

// Object types
ltn_Value test_as_array(ltn_Context * context, const ltn_Value * args);
ltn_Value test_as_tuple(ltn_Context * context, const ltn_Value * args);
ltn_Value test_as_string(ltn_Context * context, const ltn_Value * args);
ltn_Value test_as_map(ltn_Context * context, const ltn_Value * args);