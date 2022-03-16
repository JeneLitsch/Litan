#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	constexpr auto algorithm_sort_ascn = std::array{
		"algorithm 00"sv,
	};

	constexpr auto algorithm_sort_desc = std::array{
		"algorithm 01"sv,
	};

	constexpr auto algorithm_is_sorted_ascn = std::array{
		"algorithm 02"sv,
		"return"sv,
	};

	constexpr auto algorithm_is_sorted_desc = std::array{
		"algorithm 03"sv,
		"return"sv,
	};

	constexpr auto algorithm_find = std::array{
		"algorithm 10"sv,
		"return"sv,
	};

	constexpr auto algorithm_copy_front = std::array{
		"algorithm 20"sv,
	};

	constexpr auto algorithm_copy_back = std::array{
		"algorithm 22"sv,
	};

	constexpr auto algorithm_fill = std::array{
		"algorithm 30"sv,
	};

	constexpr auto algorithm_reverse = std::array{
		"algorithm 40"sv,
	};
}