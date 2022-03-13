#pragma once
#include <variant>
#include <random>
namespace ltn::vm {
	struct RandomEngine {
		constexpr static std::string_view typeName = "RandomEngine";
		std::variant<std::mt19937_64> engine;

		RandomEngine clone() const {
			return *this;
		}

		void seed(std::int64_t seed) {
			std::visit([seed](auto & rng) {
				rng.seed(seed);
			}, engine);
		}

		std::uint64_t get() {
			return std::visit([](auto & rng) {
				return rng();
			}, engine);
		}
	};
}