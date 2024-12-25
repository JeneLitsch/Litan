#pragma once
#include "Statement.hxx"

namespace ltn::c::sst::expr { struct Expression; }

namespace ltn::c::sst::stmt {
	struct Throw final : public Statement {
		Throw(expr_ptr expr);

		virtual std::size_t temporary_alloc() const override;
		virtual std::size_t persistent_alloc() const override;

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Throw();

		expr_ptr expr;
	};

	std::unique_ptr<Throw> thr0w(expr_ptr expr);
}