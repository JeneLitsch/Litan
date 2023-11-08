#include "Map.hxx"

namespace ltn::c::sst {
	Map::Map() {}

	
	
	std::uint64_t Map::alloc() const {
		std::uint64_t count = 0;
		for(const auto & [key, val] : this->pairs) {
			count = std::max(key->alloc() + val->alloc(), count);
		}
		return count;
	}



	std::unique_ptr<Map> map() {
		return std::make_unique<Map>();
	}
}