#pragma once
#include <cstdint>
#include "stdxx/casting.hxx"
#include "stdxx/float64_t.hxx"

namespace ltn::vm {
	inline std::uint64_t to_uint(stx::float64_t value) {
		return stx::bitcast<std::uint64_t>(value);
	}

	inline stx::float64_t to_float(std::uint64_t value) {
		return stx::bitcast<stx::float64_t>(value);
	}
}