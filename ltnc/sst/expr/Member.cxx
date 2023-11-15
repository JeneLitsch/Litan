#include "Member.hxx"
#include "ltnc/sst/bind/Member.hxx"

namespace ltn::c::sst::expr {
	Member::Member(expr_ptr expr, std::size_t address)
		: expr(std::move(expr))
		, address { address } {};



	std::uint64_t Member::alloc() const {
		return 0;
	}



	bind_ptr Member::convert_to_bindung() && {
		return bind::member(std::move(this->expr), this->address);
	}



	std::unique_ptr<Member> member(expr_ptr expr, std::uint64_t member) {
		return std::make_unique<Member>(std::move(expr), member);
	}
}