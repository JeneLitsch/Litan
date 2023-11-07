#pragma once
#include "Expression.hxx"
#include "ltnc/Operations.hxx"

namespace ltn::c::sst {
	struct Binary : public ExpressionCRTP<Binary> {
		using Op = BinaryOp;
		Binary(Op op, expr_ptr l, expr_ptr r);

		virtual std::uint64_t alloc() const override;

		Op op;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};
}