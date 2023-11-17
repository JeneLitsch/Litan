#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Lambda final : public Expression {
		Lambda(func_ptr fx, std::vector<std::unique_ptr<Var>> captures, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
		virtual ~Lambda();

		func_ptr fx;
		std::vector<std::unique_ptr<Var>> captures;
	};

	std::unique_ptr<Lambda> lambda(const SourceLocation & location, func_ptr fx, std::vector<std::unique_ptr<Var>> captures);
}