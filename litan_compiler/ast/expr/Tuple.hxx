#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Tuple final: public Expression {
		Tuple(const SourceLocation & location, std::vector<expr_ptr> elements);
		virtual void accept(const ExprVisitor & visitor) const override;

		std::vector<expr_ptr> elements;
	};

	std::unique_ptr<Tuple> tuple(const SourceLocation & location, std::vector<expr_ptr> elements);
}