#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct While final : public Statement {
		While(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> body);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~While();

		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
	};

	std::unique_ptr<While> wh1le(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> body);
}