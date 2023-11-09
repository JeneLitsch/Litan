#pragma once
#include <vector>
#include <utility>
#include "Statement.hxx"

namespace ltn::c::sst::expr {
	struct Expression;
}

namespace ltn::c::sst::stmt {
	struct Switch : public Statement {
		Switch();

		virtual std::uint64_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Switch();

		expr_ptr condition;
		
		std::vector<std::pair<expr_ptr, stmt_ptr>> cases;
		
		stmt_ptr d3fault;
	};

	std::unique_ptr<Switch> switch_stmt();
}