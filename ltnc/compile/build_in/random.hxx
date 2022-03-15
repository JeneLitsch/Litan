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
	
	constexpr auto random_rand = std::array{
		"random 10"sv,
		"return"sv,
	};

	constexpr auto random_rand_int = std::array{
		"random 11"sv,
		"return"sv,
	};

	constexpr auto random_rand_float = std::array{
		"random 12"sv,
		"return"sv,
	};

	constexpr auto random_split = std::array{
		"random 00"sv,
		"return"sv,
	};
}