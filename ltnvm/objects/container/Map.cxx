#include "Map.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/stdlib/map.hxx"

namespace ltn::vm {
	void Map::stringify(VMCore & core, std::ostream & oss, bool nested) {
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



	Value Map::get_member(std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::map_size>     (MemberCode::SIZE),
			wrap<stdlib::map_is_empty> (MemberCode::IS_EMTPY),
			wrap<stdlib::map_at>       (MemberCode::AT),
			wrap<stdlib::map_has>      (MemberCode::HAS),
			wrap<stdlib::map_insert>   (MemberCode::INSERT),
			wrap<stdlib::map_erase>    (MemberCode::ERASE),
			wrap<stdlib::map_keys>     (MemberCode::KEYS),
			wrap<stdlib::map_values>   (MemberCode::VALUES),
			wrap<stdlib::map_merged>   (MemberCode::MERGED),
		};
		return search_native_function_table(native_function_table, id);
	}
}