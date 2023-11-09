#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst::expr { struct Expression; }

namespace ltn::c::sst::stmt {
	struct While final : public Statement {
		While(expr_ptr condition, stmt_ptr body);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~While();

		expr_ptr condition;
		stmt_ptr body;
	};

	std::unique_ptr<While> wh1le(expr_ptr condition, stmt_ptr body);
}