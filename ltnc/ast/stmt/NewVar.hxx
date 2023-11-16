#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct NewVar final : public Statement {
		NewVar(
			bind_ptr binding,
			expr_ptr expr,
			const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~NewVar(); 

		bind_ptr binding;		
		expr_ptr expr;
	};

	std::unique_ptr<NewVar> new_local(
		bind_ptr binding,
		expr_ptr expr,
		const SourceLocation & location);
}