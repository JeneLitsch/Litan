#include "Struct.hxx"
#include <cmath>

namespace ltn::c::sst {
	Struct::Struct() {}



	std::uint64_t Struct::alloc() const {
		std::uint64_t count = 0;
		for(const auto & elem : this->members) {
			count = std::max(elem.expr->alloc(), count);
		}
		return count;
	}
}