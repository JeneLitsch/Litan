#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Array final: public Expression {
		Array(const SourceLocation & location, std::vector<expr_ptr> elements);
		virtual void accept(const ExprVisitor & visitor) const override;

		std::vector<expr_ptr> elements;
	};

	std::unique_ptr<Array> array(const SourceLocation & location, std::vector<expr_ptr> elements);
}