#pragma once
#include "Expression.hxx"

namespace ltn::c::sst {
	struct Ternary : public ExpressionCRTP<Ternary> {
		Ternary(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Expression> if_branch,
			std::unique_ptr<Expression> else_branch);

		virtual std::uint64_t alloc() const override;
	
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Expression> if_branch;
		std::unique_ptr<Expression> else_branch;
	};
}