#pragma once
#include <vector>
#include <cstdint>
#include <istream>

namespace ltn::a {
	std::vector<std::uint8_t> to_bytecode(std::istream & in);
}