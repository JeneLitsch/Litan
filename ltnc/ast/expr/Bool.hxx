#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Bool final : public Expression {
		Bool(bool value, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
		bool value;
	};

	std::unique_ptr<Bool> boolean(bool value, const SourceLocation & location);
	std::unique_ptr<Bool> boolean_false(const SourceLocation & location);
	std::unique_ptr<Bool> boolean_true(const SourceLocation & location);
}