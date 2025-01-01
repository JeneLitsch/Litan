#include "plugin.hxx"

#ifdef __linux__
#include <dlfcn.h>
#endif

#include "litan_native/plugin.h"
#include "litan_vm/plugin/callbacks.hxx"


namespace ltn::vm::stdlib {
	namespace {
		template<typename Func>
		void link_function(void * plugin_handle, const char *name, Func func) {
			*static_cast<Func*>(dlsym(plugin_handle, name)) = func;
		}



		void link_plugin(void * plugin_handle) {
			link_function<ltn_FuncGCMark>(plugin_handle, "ltn_gc_mark", plugin::callback::gc_mark);

			link_function<ltn_FuncAllocArray>(plugin_handle, "ltn_alloc_array", plugin::callback::alloc_array);
			link_function<ltn_FuncAllocTuple>(plugin_handle, "ltn_alloc_tuple", plugin::callback::alloc_tuple);
			link_function<ltn_FuncAllocMap>(plugin_handle, "ltn_alloc_map", plugin::callback::alloc_map);
			link_function<ltn_FuncAllocString>(plugin_handle, "ltn_alloc_string", plugin::callback::alloc_string);
			
			link_function<ltn_FuncValueNull>(plugin_handle, "ltn_value_null", plugin::callback::value_null);
			link_function<ltn_FuncValueBool>(plugin_handle, "ltn_value_bool", plugin::callback::value_bool);
			link_function<ltn_FuncValueInt>(plugin_handle, "ltn_value_int", plugin::callback::value_int);
			link_function<ltn_FuncValueFloat>(plugin_handle, "ltn_value_float", plugin::callback::value_float);
			link_function<ltn_FuncValueArray>(plugin_handle, "ltn_value_array", plugin::callback::value_array);
			link_function<ltn_FuncValueTuple>(plugin_handle, "ltn_value_tuple", plugin::callback::value_tuple);
			link_function<ltn_FuncValueMap>(plugin_handle, "ltn_value_map", plugin::callback::value_map);
			link_function<ltn_FuncValueString>(plugin_handle, "ltn_value_string", plugin::callback::value_string);

			link_function<ltn_FuncAsBool>(plugin_handle, "ltn_as_bool", plugin::callback::as_bool);
			link_function<ltn_FuncAsInt>(plugin_handle, "ltn_as_int", plugin::callback::as_int);
			link_function<ltn_FuncAsFloat>(plugin_handle, "ltn_as_float", plugin::callback::as_float);
			link_function<ltn_FuncAsArray>(plugin_handle, "ltn_as_array", plugin::callback::as_array);
			link_function<ltn_FuncAsTuple>(plugin_handle, "ltn_as_tuple", plugin::callback::as_tuple);
			link_function<ltn_FuncAsMap>(plugin_handle, "ltn_as_map", plugin::callback::as_map);
			link_function<ltn_FuncAsString>(plugin_handle, "ltn_as_string", plugin::callback::as_string);
			
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_null", plugin::callback::is_null);
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_bool", plugin::callback::is_bool);
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_int", plugin::callback::is_int);
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_float", plugin::callback::is_float);
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_array", plugin::callback::is_array);
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_tuple", plugin::callback::is_tuple);
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_map", plugin::callback::is_map);
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_string", plugin::callback::is_string);

			link_function<ltn_FuncArrayAt>(plugin_handle, "ltn_array_at", plugin::callback::array_at);
			link_function<ltn_FuncArrayPut>(plugin_handle, "ltn_array_put", plugin::callback::array_put);
			link_function<ltn_FuncArraySize>(plugin_handle, "ltn_array_size", plugin::callback::array_size);
			link_function<ltn_FuncArrayPush>(plugin_handle, "ltn_array_push", plugin::callback::array_push);
			link_function<ltn_FuncArrayPop>(plugin_handle, "ltn_array_pop", plugin::callback:: array_pop);
			link_function<ltn_FuncArrayInsert>(plugin_handle, "ltn_array_insert", plugin::callback::array_insert);
			link_function<ltn_FuncArrayErase>(plugin_handle, "ltn_array_erase", plugin::callback::array_erase);

			link_function<ltn_FuncStringData>(plugin_handle, "ltn_string_data", plugin::callback::string_data);
			link_function<ltn_FuncStringSize>(plugin_handle, "ltn_string_size", plugin::callback::string_size);

			link_function<ltn_FuncTupleAt>(plugin_handle, "ltn_tuple_at", plugin::callback::tuple_at);
			link_function<ltn_FuncTupleSize>(plugin_handle, "ltn_tuple_size", plugin::callback::tuple_size);

			link_function<ltn_FuncMapAt>(plugin_handle, "ltn_map_at", plugin::callback::map_at);
			link_function<ltn_FuncMapPut>(plugin_handle, "ltn_map_put", plugin::callback::map_put);
			link_function<ltn_FuncMapSize>(plugin_handle, "ltn_map_size", plugin::callback::map_size);
			link_function<ltn_FuncMapHas>(plugin_handle, "ltn_map_has", plugin::callback::map_has);
		}



		Map * load_exports(VMCore & core, Plugin * plugin) {
			void * symbol = dlsym(plugin->handle, "ltn_exports");
			ltn_NativeFunctionInfo * ltn_exports = static_cast<ltn_NativeFunctionInfo *>(symbol);
			
			Map * map = core.heap.make<Map>(&core);

			for(ltn_NativeFunctionInfo * entry = ltn_exports; entry->name && entry->handle; entry++) {
				String * key = core.heap.make<String>(entry->name);
				NativeFunctionPointer * native_function_pointer = core.heap.make<NativeFunctionPointer>(plugin, entry->handle, entry->arity, false);
				native_function_pointer->flags = entry->flags;
				(*map)[value::string(key)] = value::native_function(native_function_pointer);
			}

			return map;
		}
	}



	Value load_plugin_linux(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		String * path_str = value::as<String>(args[0]);
		std::string_view path = *path_str;
		void * handle = dlmopen(static_cast<std::int64_t>(core.fetch_id()), path.data(), RTLD_LAZY);
		if(handle == nullptr) {
			throw except::cannot_open_file(std::string{path});
		}

		ltn_PluginInfo * plugin_info = static_cast<ltn_PluginInfo *>(dlsym(handle, "ltn_plugin_info"));

		Plugin * plugin = core.heap.make<Plugin>();
		plugin->gc_mark = plugin_info->gc_mark;
		plugin->handle = handle;

		link_plugin(handle);
		plugin_info->init();

		Map * exports = load_exports(core, plugin);
		return value::map(exports);
	}



	Value load_plugin_other(Context *, const Value *) {
		throw std::runtime_error{"Plugins are only supported on Linux"};
	}
	


	Value load_plugin::func(Context * context, const Value * args){
		#ifdef __linux__ 
			return load_plugin_linux(context, args);
		#else
			return load_plugin_other(core);
		#endif
	}
}