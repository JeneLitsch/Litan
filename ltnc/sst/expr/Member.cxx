#include "Member.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst {
	Member::Member(
		std::unique_ptr<Expression> expr,
		std::size_t address)
		: expr(std::move(expr))
		, address { address } {};



	std::uint64_t Member::alloc() const {
		return 0;
	}



	std::unique_ptr<Binding> Member::convert_to_bindung() && {
		return std::make_unique<MemberBinding>(std::move(this->expr), this->address);
	}
}