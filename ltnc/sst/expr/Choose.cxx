#include "Choose.hxx"

namespace ltn::c::sst {
	Choose::Choose() {}

	std::uint64_t Choose::alloc() const {
		std::uint64_t count = 0;
		for(const auto & [c4se, expr] : this->cases) {
			count = std::max({c4se->alloc(), expr->alloc(), count});
		}
		return count;
	}


	std::unique_ptr<Choose> switch_expr() {
		return std::make_unique<Choose>();
	}
}