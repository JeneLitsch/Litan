#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst::expr { struct Expression; }

namespace ltn::c::sst::stmt {
	struct CoReturn final : public Statement {
		CoReturn(expr_ptr expr);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
	
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~CoReturn();

		expr_ptr expr;
	};


	std::unique_ptr<CoReturn> co_retvrn(expr_ptr expr);
}