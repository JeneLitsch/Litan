# C API - Creating a Plugin

For a shared library to be usable as a Litan plugin it has to fullfil a number of requirements:

1. Must contain export table 
2. Must contain plugin_info
3. Must include litan header

## Export Table

The export table list all function which will be exported to the Litan VM.  
It is an array of `ltn_NativeFunctionInfo` structs each containing the name, function pointer arity of the function.  
The last entry must be a sentinel entry(`{0,0,0}`).
The table must be named `ltn_exports`.

Example:
```C

ltn_Value foo(ltn_Context * context, const ltn_Value * args); // Use 0 args
ltn_Value bar(ltn_Context * context, const ltn_Value * args); // Use 2 args

extern ltn_NativeFunctionInfo ltn_exports[] = {
	{ "foo", foo, 0 },
	{ "bar", bar, 2 },
	{0,0,0}
};


```

## Plugin Info and Initialization

```C
void init() {
	// Code her runs once when loading the plugin
}

extern ltn_PluginInfo ltn_plugin_info = {
	.init = init,
};

```


## Litan Header

The Litan header must be included as implementation in `*.c` file exactly once.

```C
#define LTN_IMPL
#include "path/to/litan.h"
```