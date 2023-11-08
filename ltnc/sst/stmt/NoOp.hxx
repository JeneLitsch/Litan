#pragma once
#include "Statement.hxx"

namespace ltn::c::sst {
	struct NoOp : public Statement {
		NoOp();
		
		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;

		virtual void accept(const StmtVisitor & visitor) const override;
	};

	std::unique_ptr<NoOp> no_op();
}