#pragma once

#include <stdint.h>
#include <stdbool.h> 

#ifndef __STDC_IEC_559__
#error "Requires IEEE 754 flaots."
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef bool ltn_Bool;
typedef int64_t ltn_Int;
typedef double ltn_Float;
typedef void const * ltn_TypePtr;
typedef void* ltn_ObjectPtr;

typedef struct { void * ptr; } ltn_Array;
typedef struct { void * ptr; } ltn_Map;
typedef struct { void * ptr; } ltn_String;
typedef struct { void * ptr; } ltn_Tuple;


#ifdef __cplusplus
}
#endif
