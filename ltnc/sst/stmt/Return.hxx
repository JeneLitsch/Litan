#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct Return final : public Statement {
		Return(
			std::unique_ptr<Expression> expr,
			std::optional<std::string> overide_label);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
	
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Return();

		std::unique_ptr<Expression> expr;
		std::optional<std::string> overide_label;
	};


	std::unique_ptr<Return> r3turn(std::unique_ptr<Expression> expr, std::optional<std::string> overide_label);
}