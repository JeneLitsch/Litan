#include "plugin.hxx"

#ifdef __linux__
#include <dlfcn.h>
#endif
#include "native/litan.h"


namespace ltn::vm::build_in {
	Value load_plugin_linux(VMCore & core) {
		Value args_0 = core.stack.pop();
		String * path = value::as<String>(args_0);
		Map * map = core.heap.make<Map>(&core);
		void * handle = dlopen(path->get_underlying().c_str(), RTLD_LAZY);
		ltn_PluginInfo*(*ltn_init)() = reinterpret_cast<ltn_PluginInfo*(*)()>(dlsym(handle, "ltn_init"));
		ltn_PluginInfo * plugin_info = ltn_init();
		for(std::size_t i = 0; i < plugin_info->function_infos_size; i++) {
			ltn_NativeFunctionInfo entry = plugin_info->function_infos_data[i];
			String * key = core.heap.make<String>(entry.name);
			NativeFunctionPointer * value = core.heap.alloc(NativeFunctionPointer(entry.handle, entry.arity, false));
			map->get_underlying()[value::string(key)] = value::native_function(value);
		}
		return value::map(map);
	}



	Value load_plugin_other(VMCore & core) {
		throw std::runtime_error{"Plugins are only supported on Linux"};
	}
	


	Value load_plugin(VMCore & core) {
		#ifdef __linux__ 
			return load_plugin_linux(core);
		#else
			return load_plugin_other(core);
		#endif
	}
}