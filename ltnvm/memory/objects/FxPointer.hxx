#pragma once
#include <cstdint>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	struct FxPointer {
		std::uint64_t address;
		std::size_t params;
		std::size_t get_parameters() const {
			return this->params;
		}
		Array captured;
		constexpr static std::string_view typeName = "FxPointer";
		
	};



	inline FxPointer clone(const FxPointer & fx_ptr) {
		return fx_ptr;
	}
}