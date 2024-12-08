#pragma once

#include "Value.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ltn_NativeCoreSelf {
	void * core;
	ltn_Value(*alloc_array)(struct ltn_NativeCoreSelf * native_core, const ltn_Value * data, uint64_t size);
	ltn_Value(*alloc_map)(struct ltn_NativeCoreSelf * native_core, const ltn_Value * key_data, const ltn_Value * value_data, uint64_t size);
} ltn_NativeCore;

typedef ltn_Value(* ltn_NativeFunctionHandle)(ltn_NativeCore *, const ltn_Value *);

#ifdef __cplusplus
}
#endif




