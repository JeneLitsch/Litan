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
		"build_in 16"sv,
		"return"sv,
	};

	constexpr auto random_rand = std::array{
		"build_in 17"sv,
		"return"sv,
	};

	constexpr auto random_rand_int = std::array{
		"build_in 18"sv,
		"return"sv,
	};

	constexpr auto random_rand_float = std::array{
		"build_in 19"sv,
		"return"sv,
	};
}