#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Iife final : public Expression {
		Iife(const SourceLocation & location, stmt_ptr stmt);
		virtual void accept(const ExprVisitor & visitor) const override;
		virtual ~Iife();

		stmt_ptr stmt;
	};

	std::unique_ptr<Iife> iife(const SourceLocation & location, stmt_ptr stmt);
}