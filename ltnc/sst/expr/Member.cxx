#include "Member.hxx"

namespace ltn::c::sst {
	Member::Member(
		std::unique_ptr<Expression> expr,
		std::size_t address)
		: expr(std::move(expr))
		, address { address } {};

	std::uint64_t Member::alloc() const {
		return 0;
	}
}