#pragma once
#include <vector>
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct Invoke final : public ExpressionCRTP<Invoke> {
		Invoke(expr_ptr function_ptr, std::vector<expr_ptr> arguments);

		virtual std::uint64_t alloc() const override;

		std::uint64_t arity() const;

		expr_ptr function_ptr;
		std::vector<expr_ptr> arguments;
	};

	std::unique_ptr<Invoke> invoke(expr_ptr function_ptr, std::vector<expr_ptr> arguments);
}