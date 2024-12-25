#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Call final : public Expression {
		Call(expr_ptr function_ptr, std::vector<expr_ptr> arguments, const SourceLocation & location);

		virtual void accept(const ExprVisitor & visitor) const override;

		std::uint64_t arity() const;

		expr_ptr function_ptr;
		std::vector<expr_ptr> arguments;
	};

	std::unique_ptr<Call> call(const SourceLocation & location, expr_ptr function_ptr, std::vector<expr_ptr> arguments);
}