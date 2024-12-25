#include "Switch.hxx"
#include <algorithm>

namespace ltn::c::sst::expr {
	Switch::Switch() {}

	std::uint64_t Switch::alloc() const {
		std::uint64_t count = 0;
		for(const auto & [c4se, expr] : this->cases) {
			count = std::max({c4se->alloc(), expr->alloc(), count});
		}
		return count;
	}


	std::unique_ptr<Switch> sw1tch() {
		return std::make_unique<Switch>();
	}
}