#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile {
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
		"swap 0 1"sv,
		"algorithm 10"sv,
		"return"sv,
	};

	constexpr auto algorithm_copy_front = std::array{
		"swap 0 1"sv,
		"algorithm 20"sv,
	};

	constexpr auto algorithm_copy_back = std::array{
		"swap 0 1"sv,
		"algorithm 22"sv,
	};

	constexpr auto algorithm_fill = std::array{
		"swap 0 1"sv,
		"algorithm 30"sv,
	};

	constexpr auto algorithm_reverse = std::array{
		"algorithm 40"sv,
	};
}