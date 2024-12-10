#pragma once

#include "NativeCore.h"
#include "types.h"
#include "Value.h"
#include "plugin.h"

#ifdef LTN_IMPL
#define LINKED
#else
#define LINKED extern
#endif

// Allocations
LINKED ltn_FuncAllocArray ltn_alloc_array;
LINKED ltn_FuncAllocMap ltn_alloc_map;
LINKED ltn_FuncAllocString ltn_alloc_string;
LINKED ltn_FuncAllocTuple ltn_alloc_tuple;

// Wrap into value
LINKED ltn_FuncValueNull ltn_value_null;
LINKED ltn_FuncValueBool ltn_value_bool;
LINKED ltn_FuncValueChar ltn_value_char;
LINKED ltn_FuncValueInt ltn_value_int;
LINKED ltn_FuncValueFloat ltn_value_float;
LINKED ltn_FuncValueArray ltn_value_array;
LINKED ltn_FuncValueTuple ltn_value_tuple;
LINKED ltn_FuncValueMap ltn_value_map;
LINKED ltn_FuncValueString ltn_value_string;

// Casts
LINKED ltn_FuncAsBool ltn_as_bool;
LINKED ltn_FuncAsChar ltn_as_char;
LINKED ltn_FuncAsInt ltn_as_int;
LINKED ltn_FuncAsFloat ltn_as_float;
LINKED ltn_FuncAsArray ltn_as_array;
LINKED ltn_FuncAsTuple ltn_as_tuple;
LINKED ltn_FuncAsMap ltn_as_map;
LINKED ltn_FuncAsString ltn_as_string;

// Type check
LINKED ltn_FuncIsType ltn_is_null;
LINKED ltn_FuncIsType ltn_is_bool;
LINKED ltn_FuncIsType ltn_is_char;
LINKED ltn_FuncIsType ltn_is_int;
LINKED ltn_FuncIsType ltn_is_float;
LINKED ltn_FuncIsType ltn_is_array;
LINKED ltn_FuncIsType ltn_is_tuple;
LINKED ltn_FuncIsType ltn_is_map;
LINKED ltn_FuncIsType ltn_is_string;

// Array API
LINKED ltn_FuncArrayAt ltn_array_at;
LINKED ltn_FuncArrayPut ltn_array_put;
LINKED ltn_FuncArraySize ltn_array_size;
LINKED ltn_FuncArrayPush ltn_array_push;
LINKED ltn_FuncArrayPop ltn_array_pop;
LINKED ltn_FuncArrayInsert ltn_array_insert;
LINKED ltn_FuncArrayErase ltn_array_erase;

// Map API
LINKED ltn_FuncMapAt ltn_map_at;
LINKED ltn_FuncMapPut ltn_map_put;
LINKED ltn_FuncMapSize ltn_map_size;
LINKED ltn_FuncMapHas ltn_map_has;

// Tuple API
LINKED ltn_FuncTupleAt ltn_tuple_at;
LINKED ltn_FuncTupleSize ltn_tuple_size;

// String API
LINKED ltn_FuncStringData ltn_string_data;
LINKED ltn_FuncStringSize ltn_string_size;