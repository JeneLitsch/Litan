#pragma once

#include "Value.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ltn_Context {
	void * core;
} ltn_Context;


typedef ltn_Value(* ltn_NativeFunctionHandle)(ltn_Context * ctx, const ltn_Value * args);

#ifdef __cplusplus
}
#endif




