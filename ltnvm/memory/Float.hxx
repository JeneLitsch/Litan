#pragma once
#include <cstdint>
#include "ltn/bitcast.hxx"
#include "ltn/float64_t.hxx"

namespace ltn::vm {
	inline std::uint64_t to_uint(stx::float64_t value) {
		return bitcast<std::uint64_t>(value);
	}

	inline stx::float64_t to_float(std::uint64_t value) {
		return bitcast<stx::float64_t>(value);
	}
}