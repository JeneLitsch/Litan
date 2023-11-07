#include "Ternary.hxx"

namespace ltn::c::sst {
	Ternary::Ternary(
		std::unique_ptr<Expression> condition,
		std::unique_ptr<Expression> if_branch,
		std::unique_ptr<Expression> else_branch) 
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
}