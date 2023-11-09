#pragma once
#include <vector>
#include <utility>
#include "Statement.hxx"

namespace ltn::c::sst::expr {
	struct Expression;
}

namespace ltn::c::sst {
	struct Switch : public Statement {
		Switch();

		virtual std::uint64_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Switch();

		std::unique_ptr<expr::Expression> condition;
		
		std::vector<std::pair<
			std::unique_ptr<expr::Expression>,
			std::unique_ptr<Statement>
		>> cases;
		
		std::unique_ptr<Statement> d3fault;
	};

	std::unique_ptr<Switch> switch_stmt();
}