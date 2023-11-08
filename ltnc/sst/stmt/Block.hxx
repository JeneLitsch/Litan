#pragma once
#include <utility>
#include <vector>
#include "Statement.hxx"

namespace ltn::c::sst {
	struct Block final : public Statement {
		Block(std::vector<std::unique_ptr<Statement>> statements);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		std::vector<std::unique_ptr<Statement>> statements;
	};

	std::unique_ptr<Block> block(std::vector<std::unique_ptr<Statement>> statements);
}