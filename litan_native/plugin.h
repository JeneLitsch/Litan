#pragma once

#include "context.h"
#include "types.h"
#include "Value.h"

enum ltn_Flags {
	ltn_DEFAULT = 0,
	ltn_USE_GC = 1,
};

typedef struct {
	const char * name;
	ltn_NativeFunctionHandle handle;
	uint64_t arity;
	uint64_t flags;
} ltn_NativeFunctionInfo;



typedef struct {
	void(*init)(void);
	void(*gc_mark)(void);
} ltn_PluginInfo;

typedef void(*ltn_FuncGCMark)(ltn_Value value);

typedef ltn_Array(*ltn_FuncAllocArray)(ltn_Context *, const ltn_Value *, uint64_t);
typedef ltn_Tuple(*ltn_FuncAllocTuple)(ltn_Context *, const ltn_Value *, uint64_t);
typedef ltn_Map(*ltn_FuncAllocMap)(ltn_Context *, const ltn_Value *, const ltn_Value *, uint64_t);
typedef ltn_String(*ltn_FuncAllocString)(ltn_Context *, const char * data);

typedef ltn_Value(*ltn_FuncValueNull)();
typedef ltn_Value(*ltn_FuncValueBool)(ltn_Bool);
typedef ltn_Value(*ltn_FuncValueInt)(ltn_Int);
typedef ltn_Value(*ltn_FuncValueFloat)(ltn_Float);
typedef ltn_Value(*ltn_FuncValueArray)(ltn_Array);
typedef ltn_Value(*ltn_FuncValueTuple)(ltn_Tuple);
typedef ltn_Value(*ltn_FuncValueMap)(ltn_Map);
typedef ltn_Value(*ltn_FuncValueString)(ltn_String);

typedef ltn_Bool(*ltn_FuncAsBool)(ltn_Value);
typedef ltn_Int(*ltn_FuncAsInt)(ltn_Value);
typedef ltn_Float(*ltn_FuncAsFloat)(ltn_Value);
typedef ltn_Array(*ltn_FuncAsArray)(ltn_Value);
typedef ltn_Tuple(*ltn_FuncAsTuple)(ltn_Value);
typedef ltn_Map(*ltn_FuncAsMap)(ltn_Value);
typedef ltn_String(*ltn_FuncAsString)(ltn_Value);

typedef bool(*ltn_FuncIsType)(ltn_Value);

typedef ltn_Value(*ltn_FuncArrayAt)(ltn_Array, ltn_Int);
typedef void(*ltn_FuncArrayPut)(ltn_Array, ltn_Int, ltn_Value);
typedef ltn_Int(*ltn_FuncArraySize)(ltn_Array);
typedef void(*ltn_FuncArrayPush)(ltn_Array, ltn_Value);
typedef ltn_Value(*ltn_FuncArrayPop)(ltn_Array);
typedef void(*ltn_FuncArrayInsert)(ltn_Array, ltn_Int, ltn_Value);
typedef ltn_Value(*ltn_FuncArrayErase)(ltn_Array, ltn_Int);

typedef const char *(*ltn_FuncStringData)(ltn_String string);
typedef ltn_Int(*ltn_FuncStringSize)(ltn_String string);

typedef ltn_Value(*ltn_FuncMapAt)(ltn_Map map, ltn_Value key);
typedef void(*ltn_FuncMapPut)(ltn_Map map, ltn_Value key, ltn_Value value);
typedef ltn_Int(*ltn_FuncMapSize)(ltn_Map map);
typedef ltn_Bool(*ltn_FuncMapHas)(ltn_Map map, ltn_Value key);

typedef ltn_Value(*ltn_FuncTupleAt)(ltn_Tuple tuple, ltn_Int index);
typedef ltn_Int(*ltn_FuncTupleSize)(ltn_Tuple);
