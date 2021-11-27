#pragma once
#include <limits>
#include <cstdint>

// 64-bit ieee only
static_assert(std::numeric_limits<double>::is_iec559);
static_assert(sizeof(double) == sizeof(std::uint64_t));

namespace ltn::vm {
	inline std::uint64_t toUint(double value) {
		return *reinterpret_cast<std::uint64_t*>(&value);
	}

	inline double toFloat(std::uint64_t value) {
		return *reinterpret_cast<double*>(&value);
	}
}