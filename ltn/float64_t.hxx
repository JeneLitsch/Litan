#pragma once
#include <limits>
#include <cstdint>

// 64-bit ieee only
static_assert(std::numeric_limits<double>::is_iec559);
static_assert(sizeof(double) == sizeof(std::uint64_t));

namespace stx {
	using float64_t = double;
}
