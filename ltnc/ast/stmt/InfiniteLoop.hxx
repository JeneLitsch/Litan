#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct InfiniteLoop final : public Statement {
		InfiniteLoop(stmt_ptr body, const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~InfiniteLoop();

		stmt_ptr body;
	};

	std::unique_ptr<InfiniteLoop> infinite_loop(stmt_ptr body, const SourceLocation & location);
}