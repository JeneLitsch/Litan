#pragma once
#include "Expression.hxx"

namespace ltn::c::sst {
	struct Var final : public ExpressionCRTP<Var> {
		Var(std::size_t address);

		virtual std::uint64_t alloc() const override;
		virtual std::unique_ptr<Binding> convert_to_bindung() && override;

		std::size_t address;
	};
}