#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Ternary final : public Expression {
		Ternary(
			const SourceLocation & location,
			expr_ptr condition,
			expr_ptr if_branch,
			expr_ptr else_branch);
	
		virtual void accept(const ExprVisitor & visitor) const override;

		expr_ptr condition;
		expr_ptr if_branch;
		expr_ptr else_branch;
	};

	std::unique_ptr<Ternary> ternary(
		const SourceLocation & location,
		expr_ptr condition,
		expr_ptr if_branch,
		expr_ptr else_branch);
}