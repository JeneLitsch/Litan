#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct InfiniteLoop final : public Statement {
		InfiniteLoop(std::unique_ptr<Statement> body);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		std::unique_ptr<Statement> body;
	};

	std::unique_ptr<InfiniteLoop> infinite_loop(std::unique_ptr<Statement> body);
}