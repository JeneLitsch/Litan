#pragma once
#include <vector>
#include "ltnc/Label.hxx"
#include "Expression.hxx"

namespace ltn::c::sst {
	struct Call final : public ExpressionCRTP<Call> {
		Call(const Label & label, std::vector<expr_ptr> arguments);

		virtual std::uint64_t alloc() const override;
		
		std::uint64_t arity() const;

		Label label;
		std::vector<expr_ptr> arguments;
	};



	std::unique_ptr<Call> call(const Label & label, std::vector<expr_ptr> arguments);
}