#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	constexpr auto math_min = std::array{
		"min"sv,
		"return"sv,
	};
	
	constexpr auto math_max = std::array{
		"max"sv,
		"return"sv,
	};
	
	constexpr auto math_clamp = std::array{
		"makevar"sv,
		"write_0"sv,
		"max"sv,
		"read_0"sv,
		"min"sv,
		"return"sv,
	};

	constexpr auto math_round = std::array{
		"round"sv,
		"return"sv,
	};
	
	constexpr auto math_floor = std::array{
		"floor"sv,
		"return"sv,
	};
	
	constexpr auto math_ceil = std::array{
		"ceil"sv,
		"return"sv,
	};

	constexpr auto math_abs = std::array{
		"abs"sv,
		"return"sv,
	};
	
	constexpr auto math_hypot = std::array{
		"hypot"sv,
		"return"sv,
	};
	
	constexpr auto math_sqrt = std::array{
		"sqrt"sv,
		"return"sv,
	};
	
	constexpr auto math_log = std::array{
		"log"sv,
		"return"sv,
	};
	
	constexpr auto math_ld = std::array{
		"newf 2"sv,
		"log"sv,
		"return"sv,
	};
	
	constexpr auto math_lg = std::array{
		"newf 10"sv,
		"log"sv,
		"return"sv,
	};

	constexpr auto math_ln = std::array{
		"ln"sv,
		"return"sv,
	};
	
	constexpr auto math_pow = std::array{
		"pow"sv,
		"return"sv,
	};

	constexpr auto math_sin = std::array{
		"sin"sv,
		"return"sv,
	};
	
	constexpr auto math_cos = std::array{
		"cos"sv,
		"return"sv,
	};
	
	constexpr auto math_tan = std::array{
		"tan"sv,
		"return"sv,
	};
}