#include "Map.hxx"
#include "ltnvm/native/native.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	namespace {
		Value map_size(const Value * args) {
			Map * map = req_map(args + 0);
			return value::integer(std::size(*map));
		}



		Value map_is_empty(const Value * args) {
			Map * map = req_map(args + 0);
			return value::integer(std::empty(*map));
		}



		Value map_at(const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			if(map->contains(key)) {
				return map->at(key);
			}
			else {
				return value::null;
			}
		}



		Value map_has(const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			return value::boolean(map->contains(key));
		}



		Value map_insert(const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			const Value value = args[2];
			(*map)[key] = value;
			return value::null;
		}



		Value map_erase(const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			const Value value = map_at(args);
			map->erase(key);
			return value;
		}



		NativeFunctionTable native_function_table {
			wrap(MemberCode::SIZE,     map_size,     1),
			wrap(MemberCode::IS_EMTPY, map_is_empty, 1),
			wrap(MemberCode::AT,       map_at,       2),
			wrap(MemberCode::HAS,      map_has,      2),
			wrap(MemberCode::INSERT,   map_insert,   3),
			wrap(MemberCode::ERASE,    map_erase,   2),
		};
	}


	Value Map::get_member(std::uint64_t id) const {
		return search_native_function_table(native_function_table, id);
	}
}