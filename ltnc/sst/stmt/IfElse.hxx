#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct IfElse final : public Statement {
		IfElse(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> if_branch,
			std::unique_ptr<Statement> else_branch);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~IfElse();

		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> if_branch;
		std::unique_ptr<Statement> else_branch;
	};

	std::unique_ptr<IfElse> if_else(
		std::unique_ptr<Expression> condition,
		std::unique_ptr<Statement> if_branch,
		std::unique_ptr<Statement> else_branch);
}