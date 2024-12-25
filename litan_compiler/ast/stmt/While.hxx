#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct While final : public Statement {
		While(expr_ptr condition, stmt_ptr body,const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~While();

		expr_ptr condition;
		stmt_ptr body;
	};

	std::unique_ptr<While> while_loop(expr_ptr condition, stmt_ptr body, const SourceLocation & location);
}