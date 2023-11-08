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



	std::unique_ptr<bind::Binding> Member::convert_to_bindung() && {
		return std::make_unique<bind::Member>(std::move(this->expr), this->address);
	}



	std::unique_ptr<Member> member(expr_ptr expr, std::uint64_t member) {
		return std::make_unique<Member>(std::move(expr), member);
	}
}