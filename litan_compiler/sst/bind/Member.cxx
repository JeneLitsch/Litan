#include "Member.hxx"
#include "litan_compiler/sst/expr/Expression.hxx"

namespace ltn::c::sst::bind {
	Member::Member(
		expr_ptr object,
		std::uint64_t address)
		: object{std::move(object)}
		, address{address} {}



	std::size_t Member::alloc_count() const {
		return 0;
	}



	Member::~Member() {}



	std::unique_ptr<Member> member(expr_ptr object, std::uint64_t id) {
		return std::make_unique<Member>(std::move(object), id);
	}
}
