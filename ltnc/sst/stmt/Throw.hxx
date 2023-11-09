#pragma once
#include "Statement.hxx"

namespace ltn::c::sst::expr { struct Expression; }

namespace ltn::c::sst::stmt {
	struct Throw final : public Statement {
		Throw(std::unique_ptr<expr::Expression> expr);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;

		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Throw();

		std::unique_ptr<expr::Expression> expr;
	};

	std::unique_ptr<Throw> thr0w(std::unique_ptr<expr::Expression> expr);
}