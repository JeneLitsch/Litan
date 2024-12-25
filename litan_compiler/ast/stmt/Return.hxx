#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct Return final : public Statement {
		Return(expr_ptr expr, const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Return();

		expr_ptr expr;
	};

	std::unique_ptr<Return> retvrn(expr_ptr expr, const SourceLocation & location);
}
