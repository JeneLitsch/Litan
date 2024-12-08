#pragma once

#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum ltn_ValueType {
	// DO NOT TOUCH/CHANGE THE VALUES !!!
	NVLL = 0x00, TYPE,
	BOOL = 0x10, INT, FLOAT, CHAR,
	ARRAY = 0x20, STRING, TUPLE,
	ISTREAM = 0x30, OSTREAM,
	FUNCTION = 0x40, ITERATOR, ITERATOR_STOP, COROUTINE, NATIVE_FUNCTION,
	CLOCK = 0x50,
	STRUCT = 0x60,
	QUEUE = 0x70, MAP,
	RNG = 0x80, 

	FIRST_TYPE = ARRAY,
};



typedef struct {
	uint16_t type;
	union {
		ltn_Int64 i;
		ltn_Float64 f;
		ltn_Bool b;
		ltn_Char c;
		ltn_TypePtr obj_type;
		ltn_ObjectPtr object;
	};
} ltn_Value;

#ifdef __cplusplus
}
#endif

