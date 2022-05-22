#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	constexpr auto algorithm_sort_ascn = std::array{
		"build_in 00"sv,
		"return"sv,
	};

	constexpr auto algorithm_sort_desc = std::array{
		"build_in 01"sv,
		"return"sv,
	};

	constexpr auto algorithm_is_sorted_ascn = std::array{
		"build_in 02"sv,
		"return"sv,
	};

	constexpr auto algorithm_is_sorted_desc = std::array{
		"build_in 03"sv,
		"return"sv,
	};

	constexpr auto algorithm_find = std::array{
		"build_in 04"sv,
		"return"sv,
	};

	constexpr auto algorithm_copy_front = std::array{
		"build_in 05"sv,
		"return"sv,
	};

	constexpr auto algorithm_copy_back = std::array{
		"build_in 06"sv,
		"return"sv,
	};

	constexpr auto algorithm_fill = std::array{
		"build_in 07"sv,
		"return"sv,
	};

	constexpr auto algorithm_reverse = std::array{
		"build_in 08"sv,
		"return"sv,
	};
}