#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Member final : public Expression {
		Member(
			expr_ptr expr,
			const std::string & name,
			const SourceLocation & location);

		virtual void accept(const ExprVisitor & visitor) const override;

		expr_ptr expr;
		std::string name;
	};

	std::unique_ptr<Member> member(const SourceLocation & location, expr_ptr expr, const std::string & name);
}