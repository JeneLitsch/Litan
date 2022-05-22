#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	constexpr auto random_mersenne_0 = std::array{
		"newrng 00"sv,
		"return"sv,
	};

	constexpr auto random_mersenne_1 = std::array{
		"newrng 01"sv,
		"return"sv,
	};
	
	constexpr auto random_split = std::array{
		"build_in 10"sv,
		"return"sv,
	};

	constexpr auto random_rand = std::array{
		"build_in 11"sv,
		"return"sv,
	};

	constexpr auto random_rand_int = std::array{
		"build_in 12"sv,
		"return"sv,
	};

	constexpr auto random_rand_float = std::array{
		"build_in 13"sv,
		"return"sv,
	};
}