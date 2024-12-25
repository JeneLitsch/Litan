#pragma once
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct GlobalVar final : public ExpressionCRTP<GlobalVar> {
		GlobalVar(std::size_t address);

		virtual std::uint64_t alloc() const override;
		virtual bind_ptr convert_to_bindung() && override;

		std::size_t address;
	};

	std::unique_ptr<GlobalVar> var_global(std::uint64_t address);
}