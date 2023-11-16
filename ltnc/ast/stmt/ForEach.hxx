#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct ForEach final : public Statement {
		ForEach(std::string index_name, expr_ptr expr, stmt_ptr body, const SourceLocation & location);
		virtual void accept(const StmtVisitor & visitor) const override;
		virtual ~ForEach();

		std::string index_name;
		expr_ptr expr;
		stmt_ptr body;
	};

	std::unique_ptr<ForEach> for_each(std::string index_name, expr_ptr expr, stmt_ptr body, const SourceLocation & location);

}