#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Index final : public Expression {
		Index(expr_ptr expr, expr_ptr index, const SourceLocation & location);

		virtual void accept(const ExprVisitor & visitor) const override;

		expr_ptr expr;
		expr_ptr index;
	};

	std::unique_ptr<Index> index(const SourceLocation & location, expr_ptr expr, expr_ptr index);
}