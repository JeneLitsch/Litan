#pragma once
#include <cstdint>
#include <string>
namespace ltna {
	class NumberParser {
	public:
		static std::uint8_t toInt8(const std::string & str);
		static std::uint32_t toInt32(const std::string & str);
		static std::uint64_t toInt64(const std::string & str);
	};
}