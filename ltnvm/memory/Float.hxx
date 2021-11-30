#pragma once
#include <limits>
#include <cstdint>
#include "ltn/Bitcast.hxx"
// 64-bit ieee only
static_assert(std::numeric_limits<double>::is_iec559);
static_assert(sizeof(double) == sizeof(std::uint64_t));

namespace ltn::vm {
	inline std::uint64_t toUint(double value) {
		return bitcast<std::uint64_t>(value);
	}

	inline double toFloat(std::uint64_t value) {
		return bitcast<double>(value);
	}
}