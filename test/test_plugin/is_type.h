#pragma once
#include "native/litan.h"

ltn_Value test_is_null(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_bool(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_char(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_int(ltn_Context * context, const ltn_Value * args);
ltn_Value test_is_float(ltn_Context * context, const ltn_Value * args);