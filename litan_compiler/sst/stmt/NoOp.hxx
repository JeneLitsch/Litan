#pragma once
#include "Statement.hxx"

namespace ltn::c::sst::stmt {
	struct NoOp : public Statement {
		NoOp();
		
		virtual std::size_t temporary_alloc() const override;
		virtual std::size_t persistent_alloc() const override;

		virtual void accept(const StmtVisitor & visitor) const override;
	};

	std::unique_ptr<NoOp> no_op();
}