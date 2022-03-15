#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	constexpr auto cast_bool = std::array{
		"cast_bool"sv,
		"return"sv,
	};
	
	constexpr auto cast_char = std::array{
		"cast_char"sv,
		"return"sv,
	};
	
	constexpr auto cast_int = std::array{
		"cast_int"sv,
		"return"sv,
	};
	
	constexpr auto cast_float = std::array{
		"cast_float"sv,
		"return"sv,
	};
	
	constexpr auto cast_string = std::array{
		"cast_string"sv,
		"return"sv,
	};
	
	constexpr auto cast_array = std::array{
		"cast_array"sv,
		"return"sv,
	};
}