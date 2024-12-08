#pragma once

#include "NativeCore.h"
#include "Types.h"
#include "Value.h"

typedef struct {
	const char * name;
	ltn_NativeFunctionHandle handle;
	uint64_t arity;
} ltn_NativeFunctionInfo;



typedef struct {
	ltn_NativeFunctionInfo * function_infos_data;
	uint64_t function_infos_size;
} ltn_PluginInfo;