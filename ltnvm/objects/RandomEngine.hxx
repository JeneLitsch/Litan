#pragma once
#include <variant>
#include <random>
namespace ltn::vm {

	struct RandomEngine {
		constexpr static std::string_view typeName = "RandomEngine";
		using result_type = std::uint64_t;
		std::variant<std::mt19937_64> engine;



		void seed(std::int64_t seed) {
			std::visit([seed](auto & rng) {
				rng.seed(static_cast<std::uint64_t>(seed));
			}, engine);
		}

		std::uint64_t operator()() {
			return std::visit([](auto & rng) {
				return rng();
			}, engine);
		}

		auto min() {
			return std::visit([](auto & rng) {
				return rng.min();
			}, engine);
		}

		auto max() {
			return std::visit([](auto & rng) {
				return rng.max();
			}, engine);
		}

		RandomEngine split();
	};



	inline RandomEngine clone(const RandomEngine & rng) {
		return rng;
	}
}