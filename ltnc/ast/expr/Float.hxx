#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Float final : public Expression {
		Float(stx::float64_t value, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;

		stx::float64_t value;
	};


	std::unique_ptr<Float> floating(stx::float64_t value, const SourceLocation & location);
}