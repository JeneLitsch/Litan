#pragma once
#include <cstdint>
#include <vector>

namespace ltn {
    inline std::uint64_t read_u64(auto & it) {
		const auto value 
			= (static_cast<std::uint64_t>(*(it + 7)) << 8 * 0)
			+ (static_cast<std::uint64_t>(*(it + 6)) << 8 * 1)
			+ (static_cast<std::uint64_t>(*(it + 5)) << 8 * 2)
			+ (static_cast<std::uint64_t>(*(it + 4)) << 8 * 3)
			+ (static_cast<std::uint64_t>(*(it + 3)) << 8 * 4)
			+ (static_cast<std::uint64_t>(*(it + 2)) << 8 * 5)
			+ (static_cast<std::uint64_t>(*(it + 1)) << 8 * 6)
			+ (static_cast<std::uint64_t>(*(it + 0)) << 8 * 7);
		it += 8;
		return value;
	}



	inline void write_u64(std::uint64_t value, std::vector<std::uint8_t> & bytecode) {
        bytecode.push_back(static_cast<std::uint8_t>(value >> 8 * 7));
        bytecode.push_back(static_cast<std::uint8_t>(value >> 8 * 6));
        bytecode.push_back(static_cast<std::uint8_t>(value >> 8 * 5));
        bytecode.push_back(static_cast<std::uint8_t>(value >> 8 * 4));
        bytecode.push_back(static_cast<std::uint8_t>(value >> 8 * 3));
        bytecode.push_back(static_cast<std::uint8_t>(value >> 8 * 2));
        bytecode.push_back(static_cast<std::uint8_t>(value >> 8 * 1));
        bytecode.push_back(static_cast<std::uint8_t>(value >> 8 * 0));
    }



	inline std::uint8_t read_u8(auto & it) {
		const auto value = *it; 
		it += 1;
		return value;
	}



	inline void write_u8(std::uint8_t value, std::vector<std::uint8_t> & bytecode) {
        bytecode.push_back(value);

    }
}