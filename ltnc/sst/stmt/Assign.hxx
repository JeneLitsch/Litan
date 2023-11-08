#pragma once
#include "Statement.hxx"

namespace ltn::c::sst {
	namespace bind {
		struct Binding;
	}

	struct Expression;
	struct Assign final : public Statement {
		Assign(std::unique_ptr<bind::Binding> binding, std::unique_ptr<Expression> expr);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Assign();

		std::unique_ptr<bind::Binding> binding;
		std::unique_ptr<Expression> expr;
	};

	std::unique_ptr<Assign> assign(std::unique_ptr<bind::Binding> bind, std::unique_ptr<Expression> expr);
}