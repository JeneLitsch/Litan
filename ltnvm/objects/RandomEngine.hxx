#pragma once
#include <variant>
#include <random>
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {

	struct RandomEngine : public Object {
		using Variant = std::variant<std::mt19937_64>;
		RandomEngine(Variant var) : engine{std::move(var)} {}

		constexpr static std::string_view typeName = "RandomEngine";
		using result_type = std::uint64_t;

		Variant engine;


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

		auto operator()(auto dist) {
			return std::visit([&](auto & rng) {
				return dist(rng);
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