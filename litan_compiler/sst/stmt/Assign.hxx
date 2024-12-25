#pragma once
#include "Statement.hxx"

namespace ltn::c::sst::stmt {

	struct Assign final : public Statement {
		Assign(bind_ptr binding, expr_ptr expr);

		virtual std::size_t temporary_alloc() const override;
		virtual std::size_t persistent_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Assign();

		bind_ptr binding;
		expr_ptr expr;
	};

	std::unique_ptr<Assign> assign(bind_ptr bind, expr_ptr expr);
}