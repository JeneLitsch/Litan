#include "Map.hxx"
#include "ltnvm/native/native.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	namespace {
		Value map_size(NativeCore *, const Value * args) {
			Map * map = req_map(args + 0);
			return value::integer(std::size(*map));
		}



		Value map_is_empty(NativeCore *, const Value * args) {
			Map * map = req_map(args + 0);
			return value::integer(std::empty(*map));
		}



		Value map_at(NativeCore *, const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			if(map->contains(key)) {
				return map->at(key);
			}
			else {
				return value::null;
			}
		}



		Value map_has(NativeCore *, const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			return value::boolean(map->contains(key));
		}



		Value map_insert(NativeCore *, const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			const Value value = args[2];
			(*map)[key] = value;
			return value::null;
		}



		Value map_erase(NativeCore * native_core, const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			const Value value = map_at(native_core, args);
			map->erase(key);
			return value;
		}



		Value map_keys(NativeCore * native_core, const Value * args) {
			Map * map = req_map(args + 0);

			std::vector<Value> keys;
			for(auto [k, v] : map->get_underlying()) {
				keys.push_back(k);
			}
			Value array_ref = native_core->alloc_array(native_core, std::data(keys), std::size(keys));
			return array_ref;
		}



		Value map_values(NativeCore * native_core, const Value * args) {
			Map * map = req_map(args + 0);
			std::vector<Value> values;
			for(auto [k, v] : map->get_underlying()) {
				values.push_back(v);
			}
			Value array_ref = native_core->alloc_array(native_core, std::data(values), std::size(values));
			return array_ref;
		}



		Value map_merged(NativeCore * native_core, const Value * args) {
			Map * map_l = req_map(args + 0);
			Map * map_r = req_map(args + 1);
			std::vector<Value> keys;
			std::vector<Value> values;
			for(const auto & [key, value] : *map_l) {
				keys.push_back(key);
				values.push_back(value);
			}
			for(const auto & [key, value] : *map_r) {
				if(!map_l->contains(key)) {
					keys.push_back(key);
					values.push_back(value);
				}
			}
			return native_core->alloc_map(native_core, std::data(keys), std::data(values), std::size(keys));
		}



		NativeFunctionTable native_function_table {
			wrap(MemberCode::SIZE,     map_size,     1),
			wrap(MemberCode::IS_EMTPY, map_is_empty, 1),
			wrap(MemberCode::AT,       map_at,       2),
			wrap(MemberCode::HAS,      map_has,      2),
			wrap(MemberCode::INSERT,   map_insert,   3),
			wrap(MemberCode::ERASE,    map_erase,    2),
			wrap(MemberCode::KEYS,     map_keys,     1),
			wrap(MemberCode::VALUES,   map_values,   1),
			wrap(MemberCode::MERGED,   map_merged,   1),
		};
	}


	Value Map::get_member(std::uint64_t id) const {
		return search_native_function_table(native_function_table, id);
	}
}