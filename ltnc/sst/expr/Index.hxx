#pragma once
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct Index final : public ExpressionCRTP<Index> {
		Index(expr_ptr expr, expr_ptr index);

		virtual std::uint64_t alloc() const override;
		virtual bind_ptr convert_to_bindung() && override;

		expr_ptr expr;
		expr_ptr index;
	};


	std::unique_ptr<Index> index(expr_ptr expr, expr_ptr index);
}