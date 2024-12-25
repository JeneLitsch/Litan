#pragma once
#include <vector>
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct Switch final : ExpressionCRTP<Switch> {
		Switch();

		virtual std::uint64_t alloc() const override;

		expr_ptr condition;

		std::vector<std::pair<expr_ptr, expr_ptr>> cases;

		expr_ptr d3fault;
	};

	std::unique_ptr<Switch> sw1tch();
}