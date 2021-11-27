#pragma once
#include <cstdint>
#include <string_view>
namespace ltn::vm {
	struct FxPointer {
		std::uint64_t address;
		std::size_t params;
		std::size_t getParameters() const {
			return this->params;
		}
		constexpr static std::string_view typeName = "FxPointer";
	};
}