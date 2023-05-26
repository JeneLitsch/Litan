#pragma once
#include <cstdint>
#include <string_view>
#include <vector>
#include "ltnvm/Value.hxx"
namespace ltn::vm {
	struct FxPointer {
		const std::uint8_t * ptr;
		std::uint64_t params;
		std::uint64_t arity() const {
			return this->params;
		}
		std::vector<Value> captured;
		bool is_variadic = false;
		constexpr static std::string_view typeName = "FxPointer";
	};



	inline FxPointer clone(const FxPointer & fx_ptr) {
		return fx_ptr;
	}
}