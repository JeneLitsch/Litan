#pragma once
#include "Expression.hxx"

namespace ltn::c::sst {
	struct Index final : public ExpressionCRTP<Index> {
		Index(expr_ptr expr, expr_ptr index);

		virtual std::uint64_t alloc() const override;

		expr_ptr expr;
		expr_ptr index;
	};
}