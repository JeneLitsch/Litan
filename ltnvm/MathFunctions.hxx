#pragma once
#include <functional>
#include <cstdint>
#include <cmath>
#include "stdxx/float64_t.hxx"
namespace ltn::vm {
	struct Round {
		inline std::int64_t operator()(const stx::float64_t value) const {
			return static_cast<std::int64_t>(std::round(value));
		}
	};

	struct Floor {
		inline std::int64_t operator()(const stx::float64_t value) const {
			return static_cast<std::int64_t>(std::floor(value));
		}
	};

	struct Ceil {
		inline std::int64_t operator()(const stx::float64_t value) const {
			return static_cast<std::int64_t>(std::ceil(value));
		}
	};

	struct Absolute {
		inline auto operator()(const auto value) const {
			using T = decltype(value);
			return static_cast<decltype(std::int64_t{1} + value)>(std::abs(value));
		}
	};

	struct Sinus {
		inline stx::float64_t operator()(const auto value) const {
			return std::sin(static_cast<stx::float64_t>(value));
		}
	};

	struct Cosinus {
		inline stx::float64_t operator()(const auto value) const {
			return std::cos(static_cast<stx::float64_t>(value));
		}
	};

	struct Tangents {
		inline stx::float64_t operator()(const auto value) const {
			return std::tan(static_cast<stx::float64_t>(value));
		}
	};

}