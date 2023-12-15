#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct Yield final : public Statement {
		Yield(expr_ptr expr, const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Yield();

		expr_ptr expr;
	};

	std::unique_ptr<Yield> yield(expr_ptr expr, const SourceLocation & location);
}
