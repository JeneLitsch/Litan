#include "Map.hxx"
#include "ltnvm/utils/stringify.hxx"

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
}