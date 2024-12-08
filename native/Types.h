#pragma once

#include <stdint.h>
#include <stdbool.h> 

#ifndef __STDC_IEC_559__
#error "Requires IEEE 754 flaots."
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef int64_t ltn_Int64;
typedef double ltn_Float64;
typedef bool ltn_Bool;
typedef char ltn_Char;
typedef void const * ltn_TypePtr;
typedef void* ltn_ObjectPtr;

#ifdef __cplusplus
}
#endif
