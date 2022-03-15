#include "build_in.hxx"
#include <unordered_map>
#include "ltnc/CompilerError.hxx"
using namespace std::string_view_literals;
namespace ltn::c::compile {

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


	using Table = std::unordered_map<
		std::string_view,
		std::span<const std::string_view>>;

	const Table table{
		{"cast_bool",   cast_bool},
		{"cast_char",   cast_char},
		{"cast_int",    cast_int},
		{"cast_float",  cast_float},
		{"cast_string", cast_string},
		{"cast_array",  cast_array},

		{"algorithm_sort_ascn",      algorithm_sort_ascn},
		{"algorithm_sort_desc",      algorithm_sort_desc},
		{"algorithm_is_sorted_ascn", algorithm_is_sorted_ascn},
		{"algorithm_is_sorted_desc", algorithm_is_sorted_desc},
		{"algorithm_find",           algorithm_find},
		{"algorithm_copy_front",     algorithm_copy_front},
		{"algorithm_copy_back",      algorithm_copy_back},
		{"algorithm_fill",           algorithm_fill},
		{"algorithm_reverse",        algorithm_reverse},
	};
	
	std::span<const std::string_view> resolve_build_in(const std::string_view & key) {
		if(!table.contains(key)) {
			throw CompilerError{"Unknown build in: " + std::string(key)};
		}
		return table.at(key);
	}
}