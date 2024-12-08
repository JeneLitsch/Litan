#include "native/litan.h"

ltn_Value test(ltn_NativeCore * native_core, const ltn_Value * args) {
	ltn_Value return_value = {
		.i = 42,
		.type = INT,
	};
	return return_value;
}



ltn_Value add(ltn_NativeCore * native_core, const ltn_Value * args) {
	ltn_Value return_value = {
		.i = args[0].i + args[1].i,
		.type = INT,
	};
	return return_value;
}




ltn_PluginInfo * ltn_init() {
	static ltn_NativeFunctionInfo function_infos[] = {
		{ "test", test, 0 },
		{ "add", add, 2 },
		{0,0,0}
	};

	static ltn_PluginInfo plugin_info = { function_infos, 2 };
	return &plugin_info;
}