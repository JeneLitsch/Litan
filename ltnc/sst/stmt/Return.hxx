#pragma once
#include <optional>
#include "Statement.hxx"

namespace ltn::c::sst::expr { struct Expression; }

namespace ltn::c::sst::stmt {
	struct Return final : public Statement {
		Return(
			expr_ptr expr,
			std::optional<std::string> overide_label);

		virtual std::size_t temporary_alloc() const override;
		virtual std::size_t persistent_alloc() const override;
	
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~Return();

		expr_ptr expr;
		std::optional<std::string> overide_label;
	};


	std::unique_ptr<Return> r3turn(expr_ptr expr, std::optional<std::string> overide_label);
}