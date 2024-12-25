#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct Throw final : public Statement {
		Throw(expr_ptr expr, const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Throw();

		expr_ptr expr;
	};

	std::unique_ptr<Throw> thr0w(expr_ptr expr, const SourceLocation & location);
}