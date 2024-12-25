#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Unary final : public Expression {
		using Op = UnaryOp;
		
		Unary(Op op, expr_ptr expr, const SourceLocation & location);

		virtual void accept(const ExprVisitor & visitor) const override;

		Op op;
		expr_ptr expr;
	};

	std::unique_ptr<Unary> unary(const SourceLocation & location, Unary::Op op, expr_ptr expr);
}