#pragma once
#include <vector>
#include <cstdint>
#include <istream>
namespace ltn::a::assemble {
	std::vector<std::uint8_t> assemble(std::istream & in);
}