#pragma once
#include <functional>
#include <cstdint>
#include <cmath>
namespace ltn::vm {
	struct Round {
		constexpr inline std::int64_t operator()(const double value) const {
			return static_cast<std::int64_t>(std::round(value));
		}
	};

	struct Floor {
		constexpr inline std::int64_t operator()(const double value) const {
			return static_cast<std::int64_t>(std::floor(value));
		}
	};

	struct Ceil {
		constexpr inline std::int64_t operator()(const double value) const {
			return static_cast<std::int64_t>(std::ceil(value));
		}
	};

	struct Absolute {
		constexpr inline auto operator()(const auto value) const {
			using T = decltype(value);
			if constexpr(std::same_as<T, const bool>) {
				return value;
			}
			else {
				return static_cast<decltype(value)>(std::abs(value));
			}
		}
	};

	struct Sinus {
		constexpr inline double operator()(const auto value) const {
			return std::sin(static_cast<double>(value));
		}
	};

	struct Cosinus {
		constexpr inline double operator()(const auto value) const {
			return std::cos(static_cast<double>(value));
		}
	};

	struct Tangents {
		constexpr inline double operator()(const auto value) const {
			return std::tan(static_cast<double>(value));
		}
	};

}