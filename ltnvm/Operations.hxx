#pragma once
#include <functional>
#include <cmath>
#include <cstdint>
namespace ltn::vm {

	// Promotes operands to at least int64
	// Bool --> Int -?> Double
	template<class Op>
	struct Promoted {
		constexpr inline auto operator()(const auto l, const auto r) const {
			constexpr Op op{};
			using T = decltype(l+r+std::int64_t(1));
			return op(static_cast<T>(l), static_cast<T>(r));
		}
	};

	using Addition = Promoted<std::plus<void>>;
	using Subtraction = Promoted<std::minus<void>>;
	using Multiplication = Promoted<std::multiplies<void>>;
	
	struct Division {
		constexpr auto operator()(const auto l, const auto r) const {
			using T = decltype(l+r+std::int64_t(1));
			if(r != 0) {
				return static_cast<T>(l) / static_cast<T>(r);
			}
			// Catch zero division
			throw std::runtime_error{"Division by 0"};
		}
	};

	struct Modulo {
		constexpr auto operator()(const auto l, const auto r) const {
			using T = decltype(l+r+std::int64_t(1));
			if(r != 0) {
				if constexpr(std::integral<T>) {
					return static_cast<std::int64_t>(l%r);
				}
				else {
					return std::fmod(l, r);
				}
			}
			// Catch zero division
			throw std::runtime_error{"Modulo by 0"};
		}
	};
}