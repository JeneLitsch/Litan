#pragma once
#include <cstdint>
#include <string>
namespace ltn::a {
	std::uint8_t toInt8(const std::string & str);
	std::uint32_t toInt32(const std::string & str);
	std::uint64_t toInt64(const std::string & str);
}