#pragma once
#include "Expression.hxx"
#include "litan_compiler/Operations.hxx"

namespace ltn::c::sst::expr {
	struct Unary : public ExpressionCRTP<Unary> {
		using Op = UnaryOp;
		
		Unary(Op op, expr_ptr expr);

		virtual std::uint64_t alloc() const override;

		Op op;
		expr_ptr expr;
	};

	std::unique_ptr<Unary> unary(Unary::Op op, expr_ptr expr);
}