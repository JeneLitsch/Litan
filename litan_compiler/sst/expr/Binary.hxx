#pragma once
#include "Expression.hxx"
#include "litan_compiler/Operations.hxx"

namespace ltn::c::sst::expr {
	struct Binary : public ExpressionCRTP<Binary> {
		using Op = BinaryOp;
		Binary(Op op, expr_ptr l, expr_ptr r);

		virtual std::uint64_t alloc() const override;

		Op op;
		expr_ptr l;
		expr_ptr r;
	};

	std::unique_ptr<Binary> binary(Binary::Op op, expr_ptr l, expr_ptr r);
}