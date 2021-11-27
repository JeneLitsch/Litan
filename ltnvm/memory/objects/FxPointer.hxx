#pragma once
#include <cstdint>
namespace ltn::vm {
	struct FxPointer {
		std::uint64_t address;
		std::size_t params;
		std::size_t getParameters() const {
			return this->params;
		}
	};
}