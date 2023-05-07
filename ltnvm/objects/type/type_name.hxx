#pragma once
#include <cstdint>
#include <string>

namespace ltn::vm {
	struct Type;

	std::string type_name(const std::uint8_t * code);
	std::string type_name(const Type & type);
}