#pragma once
#include <vector>
#include <cstdint>

namespace ltn::vm {
	struct Type {
		std::vector<std::uint8_t> code;
	};

	inline Type clone(const Type & type) {
		return type;
	}
}