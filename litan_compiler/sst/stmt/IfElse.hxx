#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst::stmt {
	struct IfElse final : public Statement {
		IfElse(
			expr_ptr condition,
			stmt_ptr if_branch,
			stmt_ptr else_branch);

		virtual std::size_t temporary_alloc() const override;
		virtual std::size_t persistent_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~IfElse();

		expr_ptr condition;
		stmt_ptr if_branch;
		stmt_ptr else_branch;
	};

	std::unique_ptr<IfElse> if_else(
		expr_ptr condition,
		stmt_ptr if_branch,
		stmt_ptr else_branch);
	
	std::unique_ptr<IfElse> if_only(
		expr_ptr condition,
		stmt_ptr if_branch);
}