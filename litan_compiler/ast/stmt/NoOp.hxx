#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct NoOp final : public Statement {
		NoOp(const SourceLocation & location);
		virtual void accept(const StmtVisitor & visitor) const override;
	};

	std::unique_ptr<NoOp> no_op(const SourceLocation & location);
}