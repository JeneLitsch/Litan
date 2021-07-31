#pragma once
#include <cstdint>

namespace ltn {
	enum class OuputFormat : std::uint8_t {
		NEWLINE,
		FLOAT,
		INT,
		UINT,
		STRING,
		
	};
}