#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Binary final : public Expression {
		using Op = BinaryOp;

		Binary(Op op, expr_ptr l, expr_ptr r, const SourceLocation & location);

		virtual void accept(const ExprVisitor & visitor) const override;

		Op op;
		expr_ptr l;
		expr_ptr r;
	};

	std::unique_ptr<Binary> binary(Binary::Op op, expr_ptr l, expr_ptr r, const SourceLocation & location);
}