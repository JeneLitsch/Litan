#pragma once
#include <cstdint>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	struct FxPointer {
		std::uint64_t address;
		std::size_t params;
		std::size_t getParameters() const {
			return this->params;
		}
		std::vector<Value> captured;
		constexpr static std::string_view typeName = "FxPointer";
		
		auto clone() const {
			return *this;
		}
	};
}