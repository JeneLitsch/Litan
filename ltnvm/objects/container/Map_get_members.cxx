#include "Map.hxx"
#include "ltnvm/native/native.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/VMCore.hxx"

namespace ltn::vm {
	namespace {
		Value map_size(Context *, const Value * args) {
			Map * map = req_map(args + 0);
			return value::integer(std::size(*map));
		}



		Value map_is_empty(Context *, const Value * args) {
			Map * map = req_map(args + 0);
			return value::integer(std::empty(*map));
		}



		Value map_at(Context *, const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			return map->at(key);
		}



		Value map_has(Context *, const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			return value::boolean(map->contains(key));
		}



		Value map_insert(Context *, const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			const Value value = args[2];
			(*map)[key] = value;
			return value::null;
		}



		Value map_erase(Context * context, const Value * args) {
			Map * map = req_map(args + 0);
			const Value key = args[1];
			const Value value = map_at(context, args);
			map->erase(key);
			return value;
		}



		Value map_keys(Context * context, const Value * args) {
			VMCore & core = *static_cast<VMCore*>(context->core);
			Map * map = req_map(args + 0);
			Array * keys = core.heap.alloc(map->keys());
			return value::array(keys);
		}



		Value map_values(Context * context, const Value * args) {
			VMCore & core = *static_cast<VMCore*>(context->core);
			Map * map = req_map(args + 0);
			Array * values = core.heap.alloc(map->values());
			return value::array(values);
		}



		Value map_merged(Context * context, const Value * args) {
			VMCore & core = *static_cast<VMCore*>(context->core);
			Map * map_l = req_map(args + 0);
			Map * map_r = req_map(args + 1);
			Map * merged_map = core.heap.alloc(map_l->merged(*map_r));
			return value::map(merged_map);
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
			wrap(MemberCode::MERGED,   map_merged,   2),
		};
	}


	Value Map::get_member(std::uint64_t id) const {
		return search_native_function_table(native_function_table, id);
	}
}