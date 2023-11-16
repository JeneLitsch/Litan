#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct StatementExpression final : public Statement {
		StatementExpression(expr_ptr expr, const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~StatementExpression();

		expr_ptr expr;
	};

	std::unique_ptr<StatementExpression> just_an_expr(expr_ptr expr, const SourceLocation & location);
}