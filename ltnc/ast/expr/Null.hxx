#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Null final : public Expression {
		Null(const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
	};

	std::unique_ptr<Null> null(const SourceLocation & location);
}