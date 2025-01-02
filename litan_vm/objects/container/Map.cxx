#include "Map.hxx"
#include "litan_vm/utils/stringify.hxx"
#include "litan_vm/stdlib/map.hxx"

namespace ltn::vm {
	void Map::stringify(VMCore & core, std::ostream & oss, bool) {
		if(this->empty()) {
			oss << "[:]";
		}
		else {
			print_all(std::begin(*this), std::end(*this), oss, core, '[', ']');
		}
	}

	Array Map::keys() const {
		Array keys;
		for(auto [k, v] : map) {
			keys.push_back(k);
		}
		return keys;
	}


	Array Map::values() const {
		Array values;
		for(auto [k, v] : map) {
			values.push_back(v);
		}
		return values;
	}



	Map Map::merged(const Map & other) const {
		Map merged_map{core};
		for(const auto & [key, value] : *this) {
			merged_map[key] = value;
		}
		for(const auto & [key, value] : other) {
			if(!this->contains(key)) {
				merged_map[key] = value;
			}
		}
		return  merged_map;
	}



	Value Map::get_member(VMCore & core, std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::map_size>     (ReservedMemberCode::SIZE),
			wrap<stdlib::map_is_empty> (ReservedMemberCode::IS_EMTPY),
			wrap<stdlib::map_at>       (ReservedMemberCode::AT),
			wrap<stdlib::map_has>      (ReservedMemberCode::HAS),
			wrap<stdlib::map_insert>   (ReservedMemberCode::INSERT),
			wrap<stdlib::map_erase>    (ReservedMemberCode::ERASE),
			wrap<stdlib::map_keys>     (ReservedMemberCode::KEYS),
			wrap<stdlib::map_values>   (ReservedMemberCode::VALUES),
			wrap<stdlib::map_merged>   (ReservedMemberCode::MERGED),
		};
		return search_native_function_table(native_function_table, id);
	}
}