#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst::stmt {
	struct InfiniteLoop final : public Statement {
		InfiniteLoop(stmt_ptr body);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		stmt_ptr body;
	};

	std::unique_ptr<InfiniteLoop> infinite_loop(stmt_ptr body);
}