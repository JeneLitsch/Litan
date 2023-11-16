#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct Switch : Statement {
		Switch(const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		expr_ptr condition;

		std::vector<std::pair<
			expr_ptr,
			stmt_ptr
		>> cases;

		stmt_ptr d3fault;
	};

	std::unique_ptr<Switch> sw1tch(const SourceLocation & location);
}