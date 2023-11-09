#pragma once
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct Var final : public ExpressionCRTP<Var> {
		Var(std::size_t address);

		virtual std::uint64_t alloc() const override;
		virtual bind_ptr convert_to_bindung() && override;

		std::size_t address;
	};

	std::unique_ptr<Var> var_local(std::uint64_t address);
}