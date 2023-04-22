#pragma once
#include <cstdint>
#include <string_view>
#include <vector>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	struct FxPointer {
		const std::uint8_t * ptr;
		std::size_t params;
		std::size_t get_parameters() const {
			return this->params;
		}
		std::vector<Value> captured;
		constexpr static std::string_view typeName = "FxPointer";
		
		bool marked = false;
		bool in_use = false;
	};



	inline FxPointer clone(const FxPointer & fx_ptr) {
		return fx_ptr;
	}
}