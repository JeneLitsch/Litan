#include "plugin.hxx"

#ifdef __linux__
#include <dlfcn.h>
#endif
#include "native/plugin.h"


namespace ltn::vm::build_in {
	namespace {
		void gc_mark(Value value) {
			gc::mark(value);
		}



		ltn_Array alloc_array(Context * mative_core, const Value * data, uint64_t size) {
			VMCore * core = static_cast<VMCore*>(mative_core->core); 
			core->heap.collect_garbage(core->stack);
			Array * array = core->heap.alloc<Array>(Array());
			if (data) {
				for(std::size_t i = 0; i < size; i++) {
					array->push_back(data[i]);
				}
			}
			return ltn_Array{.ptr = static_cast<void*>(array)};
		}



		ltn_Tuple alloc_tuple(Context * mative_core, const Value * data, uint64_t size) {
			VMCore * core = static_cast<VMCore*>(mative_core->core); 
			core->heap.collect_garbage(core->stack);
			Tuple * tuple = core->heap.make<Tuple>();
			if (data) {
				for(std::size_t i = 0; i < size; i++) {
					tuple->push_back(data[i]);
				}
			}
			return ltn_Tuple{.ptr = static_cast<void*>(tuple)};
		}


		
		ltn_Map alloc_map(Context * mative_core, const Value * key_data, const Value * value_data, uint64_t size) {
			VMCore * core = static_cast<VMCore*>(mative_core->core); 
			core->heap.collect_garbage(core->stack);
			Map * map = core->heap.alloc<Map>(Map(core));
			Map::std_map & std_map = map->get_underlying();
			for(std::size_t i = 0; i < size; i++) {
				std_map[key_data[i]] = value_data[i];
			}
			return ltn_Map{.ptr = static_cast<void*>(map)};
		}



		ltn_String alloc_string(Context * mative_core, const char * data) {
			VMCore * core = static_cast<VMCore*>(mative_core->core); 
			core->heap.collect_garbage(core->stack);
			String * string = core->heap.alloc<String>(std::string{data});
			return ltn_String{.ptr = static_cast<void*>(string)};
		}



		Value value_array(ltn_Array array) {
			return value::array(static_cast<Array*>(array.ptr));
		}
		


		Value value_tuple(ltn_Tuple array) {
			return value::tuple(static_cast<Tuple*>(array.ptr));
		}
		


		Value value_map(ltn_Map array) {
			return value::map(static_cast<Map*>(array.ptr));
		}



		Value value_string(ltn_String string) {
			return value::string(static_cast<String*>(string.ptr));
		}


		auto as_bool(Value value) {
			if (!is_bool(value)) {
				throw except::invalid_argument();
			}
			return value.b;
		}


		auto as_char(Value value) {
			if (!is_char(value)) {
				throw except::invalid_argument();
			}
			return value.c;
		}


		auto as_int(Value value) {
			if (!is_int(value)) {
				throw except::invalid_argument();
			}
			return value.i;
		}


		auto as_float(Value value) {
			if (!is_float(value)) {
				throw except::invalid_argument();
			}
			return value.f;
		}


		auto as_array(Value value) {
			if (!is_array(value)) {
				throw except::invalid_argument();
			}
			return ltn_Array{ .ptr = value.object };
		}


		ltn_Tuple as_tuple(Value value) {
			if (!is_tuple(value)) {
				throw except::invalid_argument();
			}
			return ltn_Tuple{ .ptr = value.object };
		}


		auto as_map(Value value) {
			if (!is_map(value)) {
				throw except::invalid_argument();
			}
			return ltn_Map{ .ptr = value.object };
		}
		

		auto as_string(Value value) {
			if (!is_string(value)) {
				throw except::invalid_argument();
			}
			return ltn_String{ .ptr = value.object };
		}



		template<typename Func>
		void link_function(void * plugin_handle, const char *name, Func func) {
			*static_cast<Func*>(dlsym(plugin_handle, name)) = func;
		}



		Value array_at(ltn_Array array, int64_t i) {
			return static_cast<Array*>(array.ptr)->at(i);
		}



		void array_put(ltn_Array array, int64_t i, Value value) {
			static_cast<Array*>(array.ptr)->at(i) = value;
		}



		int64_t array_size(ltn_Array array) {
			return static_cast<Array*>(array.ptr)->size();
		}



		void array_push(ltn_Array array, Value value) {
			return static_cast<Array*>(array.ptr)->push_back(value);
		}



		Value array_pop(ltn_Array array) {
			return static_cast<Array*>(array.ptr)->pop_back();
		}



		void array_insert(ltn_Array array, std::int64_t i, Value value) {
			return static_cast<Array*>(array.ptr)->insert(i, value);
		}



		Value array_erase(ltn_Array array, std::int64_t i) {
			return static_cast<Array*>(array.ptr)->erase(i);
		}



		const char * string_data(ltn_String string) {
			return static_cast<String*>(string.ptr)->get_underlying().c_str();
		}



		int64_t string_size(ltn_String string) {
			return static_cast<String*>(string.ptr)->get_underlying().size();
		}


		Value map_at(ltn_Map map, Value key) {
			return static_cast<Map*>(map.ptr)->at(key);
		}


		void map_put(ltn_Map map, Value key, Value value) {
			static_cast<Map*>(map.ptr)->get_underlying()[key] = value;
		}


		int64_t map_size(ltn_Map map) {
			return static_cast<Map*>(map.ptr)->size();
		}


		bool map_has(ltn_Map map, Value key) {
			return static_cast<Map*>(map.ptr)->contains(key);
		}


		Value tuple_at(ltn_Tuple tuple, ltn_Int index) {
			Tuple * t = static_cast<Tuple*>(tuple.ptr);
			if(t->size() <= index) {
				throw except::out_of_range();
			}
			return t->unsafe_at(index);
		}

		int64_t tuple_size(ltn_Tuple tuple) {
			return static_cast<Tuple*>(tuple.ptr)->size();
		}



		void link_plugin(void * plugin_handle) {
			link_function<ltn_FuncGCMark>(plugin_handle, "ltn_gc_mark", gc_mark);

			link_function<ltn_FuncAllocArray>(plugin_handle, "ltn_alloc_array", alloc_array);
			link_function<ltn_FuncAllocTuple>(plugin_handle, "ltn_alloc_tuple", alloc_tuple);
			link_function<ltn_FuncAllocMap>(plugin_handle, "ltn_alloc_map", alloc_map);
			link_function<ltn_FuncAllocString>(plugin_handle, "ltn_alloc_string", alloc_string);
			
			link_function<ltn_FuncValueNull>(plugin_handle, "ltn_value_null", []() -> Value { return value::null; });
			link_function<ltn_FuncValueBool>(plugin_handle, "ltn_value_bool", value::boolean);
			link_function<ltn_FuncValueChar>(plugin_handle, "ltn_value_char", value::character);
			link_function<ltn_FuncValueInt>(plugin_handle, "ltn_value_int", value::integer<std::int64_t>);
			link_function<ltn_FuncValueFloat>(plugin_handle, "ltn_value_float", value::floating<double>);
			link_function<ltn_FuncValueArray>(plugin_handle, "ltn_value_array", value_array);
			link_function<ltn_FuncValueTuple>(plugin_handle, "ltn_value_tuple", value_tuple);
			link_function<ltn_FuncValueMap>(plugin_handle, "ltn_value_map", value_map);
			link_function<ltn_FuncValueString>(plugin_handle, "ltn_value_string", value_string);

			link_function<ltn_FuncAsBool>(plugin_handle, "ltn_as_bool", as_bool);
			link_function<ltn_FuncAsChar>(plugin_handle, "ltn_as_char", as_char);
			link_function<ltn_FuncAsInt>(plugin_handle, "ltn_as_int", as_int);
			link_function<ltn_FuncAsFloat>(plugin_handle, "ltn_as_float", as_float);
			link_function<ltn_FuncAsArray>(plugin_handle, "ltn_as_array", as_array);
			link_function<ltn_FuncAsTuple>(plugin_handle, "ltn_as_tuple", as_tuple);
			link_function<ltn_FuncAsMap>(plugin_handle, "ltn_as_map", as_map);
			link_function<ltn_FuncAsString>(plugin_handle, "ltn_as_string", as_string);
			
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_null", [](Value v) -> bool {return is_null(v);});
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_bool", [](Value v) -> bool {return is_bool(v);});
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_char", [](Value v) -> bool {return is_char(v);});
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_int", [](Value v) -> bool {return is_int(v);});
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_float", [](Value v) -> bool {return is_float(v);});
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_array", [](Value v) -> bool {return is_array(v);});
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_tuple", [](Value v) -> bool {return is_tuple(v);});
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_map", [](Value v) -> bool {return is_map(v);});
			link_function<ltn_FuncIsType>(plugin_handle, "ltn_is_string",[](Value v) -> bool {return is_string(v);});

			link_function<ltn_FuncArrayAt>(plugin_handle, "ltn_array_at", array_at);
			link_function<ltn_FuncArrayPut>(plugin_handle, "ltn_array_put", array_put);
			link_function<ltn_FuncArraySize>(plugin_handle, "ltn_array_size", array_size);
			link_function<ltn_FuncArrayPush>(plugin_handle, "ltn_array_push", array_push);
			link_function<ltn_FuncArrayPop>(plugin_handle, "ltn_array_pop",  array_pop);
			link_function<ltn_FuncArrayInsert>(plugin_handle, "ltn_array_insert", array_insert);
			link_function<ltn_FuncArrayErase>(plugin_handle, "ltn_array_erase", array_erase);

			link_function<ltn_FuncStringData>(plugin_handle, "ltn_string_data", string_data);
			link_function<ltn_FuncStringSize>(plugin_handle, "ltn_string_size", string_size);

			link_function<ltn_FuncTupleAt>(plugin_handle, "ltn_tuple_at", tuple_at);
			link_function<ltn_FuncTupleSize>(plugin_handle, "ltn_tuple_size", tuple_size);

			link_function<ltn_FuncMapAt>(plugin_handle, "ltn_map_at", map_at);
			link_function<ltn_FuncMapPut>(plugin_handle, "ltn_map_put", map_put);
			link_function<ltn_FuncMapSize>(plugin_handle, "ltn_map_size", map_size);
			link_function<ltn_FuncMapHas>(plugin_handle, "ltn_map_has", map_has);
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



	Value load_plugin_linux(VMCore & core) {
		Value args_0 = core.stack.pop();
		String * path = value::as<String>(args_0);
		void * handle = dlmopen(core.fetch_id(), path->get_underlying().c_str(), RTLD_LAZY);
		if(handle == nullptr) {
			throw except::cannot_open_file(path->get_underlying());
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