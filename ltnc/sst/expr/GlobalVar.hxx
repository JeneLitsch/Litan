#pragma once
#include "Expression.hxx"

namespace ltn::c::sst {
	struct GlobalVar final : public ExpressionCRTP<GlobalVar> {
		GlobalVar(std::size_t address);

		virtual std::uint64_t alloc() const override;
		virtual std::unique_ptr<bind::Binding> convert_to_bindung() && override;

		std::size_t address;
	};

	std::unique_ptr<GlobalVar> var_global(std::uint64_t address);
}