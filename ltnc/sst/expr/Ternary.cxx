#include "Ternary.hxx"

namespace ltn::c::sst::expr {
	Ternary::Ternary(
		expr_ptr condition,
		expr_ptr if_branch,
		expr_ptr else_branch) 
		: condition(std::move(condition))
		, if_branch(std::move(if_branch))
		, else_branch(std::move(else_branch)) {}



	std::uint64_t Ternary::alloc() const {
		return std::max({
			condition->alloc(),
			if_branch->alloc(),
			else_branch->alloc(),
		});
	}



	std::unique_ptr<Ternary> ternary(expr_ptr condition, expr_ptr if_branch, expr_ptr else_branch) {
		return std::make_unique<Ternary>(std::move(condition), std::move(if_branch), std::move(else_branch));
	}
}