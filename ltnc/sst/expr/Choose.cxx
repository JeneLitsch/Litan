#include "Choose.hxx"

namespace ltn::c::sst::expr {
	Choose::Choose() {}

	std::uint64_t Choose::alloc() const {
		std::uint64_t count = 0;
		for(const auto & [c4se, expr] : this->cases) {
			count = std::max({c4se->alloc(), expr->alloc(), count});
		}
		return count;
	}


	std::unique_ptr<Choose> sw1tch() {
		return std::make_unique<Choose>();
	}
}