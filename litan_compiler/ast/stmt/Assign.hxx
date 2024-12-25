#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct Assign final : public Statement {
	public:
		Assign(expr_ptr l, expr_ptr r, const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;
		virtual ~Assign();

		expr_ptr l;
		expr_ptr r;
	};

	std::unique_ptr<Assign> assign(expr_ptr l, expr_ptr r, const SourceLocation & location);
}