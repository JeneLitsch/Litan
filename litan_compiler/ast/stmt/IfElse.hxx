#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct IfElse final : public Statement {
		IfElse(
			expr_ptr condition,
			stmt_ptr if_branch,
			stmt_ptr else_branch,
			const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~IfElse();

		expr_ptr condition;
		stmt_ptr if_branch;
		stmt_ptr else_branch;
	};

	std::unique_ptr<IfElse> if_else(
		expr_ptr condition,
		stmt_ptr if_branch,
		stmt_ptr else_branch,
		const SourceLocation & location);
}