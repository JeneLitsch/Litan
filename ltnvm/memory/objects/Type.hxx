#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace ltn::vm {
	struct Type {
		std::vector<std::uint8_t> code;
	};

	inline Type clone(const Type & type) {
		return type;
	}

	std::string to_type_name(const std::uint8_t * code);
	std::string to_type_name(const Type & type);
}