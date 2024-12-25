#pragma once
#include <vector>
#include <cstdint>
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct Type final : ExpressionCRTP<Type> {
		Type(std::vector<std::uint8_t> type_code);

		virtual std::uint64_t alloc() const override;

		std::vector<std::uint8_t> type_code;
	};



	std::unique_ptr<Type> type(std::vector<std::uint8_t> code);
}