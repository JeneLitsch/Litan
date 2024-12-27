#pragma once

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif







typedef struct {
	uint16_t type;
	union {
		ltn_Int i;
		ltn_Float f;
		ltn_Bool b;
		ltn_TypePtr obj_type;
		ltn_ObjectPtr object;
	};
} ltn_Value;

#ifdef __cplusplus
}
#endif

