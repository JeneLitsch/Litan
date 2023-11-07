#pragma once
#include "Expression.hxx"

namespace ltn::c::sst {
	struct Ternary : public ExpressionCRTP<Ternary> {
		Ternary(
			expr_ptr condition,
			expr_ptr if_branch,
			expr_ptr else_branch);

		virtual std::uint64_t alloc() const override;
	
		expr_ptr condition;
		expr_ptr if_branch;
		expr_ptr else_branch;
	};
}