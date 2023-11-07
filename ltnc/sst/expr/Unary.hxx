#pragma once
#include "Expression.hxx"
#include "ltnc/Operations.hxx"

namespace ltn::c::sst {
	struct Unary : public ExpressionCRTP<Unary> {
		using Op = UnaryOp;
		
		Unary(Op op, expr_ptr expr);

		virtual std::uint64_t alloc() const override;

		Op op;
		expr_ptr expr;
	};
}