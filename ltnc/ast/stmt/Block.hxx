#pragma once
#include "Statement.hxx"

namespace ltn::c::ast::stmt {
	struct Block final : public Statement {
		Block(std::vector<stmt_ptr> statements, const SourceLocation & location);

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Block();

		std::vector<stmt_ptr> statements;
	};

	std::unique_ptr<Block> block(std::vector<stmt_ptr> statements, const SourceLocation & location);
}