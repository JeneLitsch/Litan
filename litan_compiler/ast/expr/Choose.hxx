#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Choose final : Expression {
		Choose(const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
		
		expr_ptr condition;
		
		std::vector<std::pair<
			expr_ptr,
			expr_ptr
		>> cases;
		
		expr_ptr d3fault;
	};

	std::unique_ptr<Choose> sw1tch(const SourceLocation & location);
}