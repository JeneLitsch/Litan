#pragma once
#include <utility>
#include <vector>
#include "Statement.hxx"

namespace ltn::c::sst::stmt {
	struct Block final : public Statement {
		Block(std::vector<stmt_ptr> statements);

		virtual std::size_t temporary_alloc() const override;
		virtual std::size_t persistent_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		std::vector<stmt_ptr> statements;
	};

	std::unique_ptr<Block> block(std::vector<stmt_ptr> statements);
}