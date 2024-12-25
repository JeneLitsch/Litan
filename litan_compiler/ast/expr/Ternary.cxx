#include "Ternary.hxx"

namespace ltn::c::ast::expr {
	Ternary::Ternary(
		const SourceLocation & location,
		expr_ptr condition,
		expr_ptr if_branch,
		expr_ptr else_branch) 
		: Expression(location)
		, condition(std::move(condition))
		, if_branch(std::move(if_branch))
		, else_branch(std::move(else_branch)) {}



	void Ternary::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Ternary> ternary(
		const SourceLocation & location,
		expr_ptr condition,
		expr_ptr if_branch,
		expr_ptr else_branch) {
		return std::make_unique<Ternary>(location, std::move(condition), std::move(if_branch), std::move(else_branch));
	}
}