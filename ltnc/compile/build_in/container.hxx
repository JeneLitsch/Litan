#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	constexpr auto container_push = std::array{
		"push"sv,
	};

	constexpr auto container_pop = std::array{
		"pop"sv,
		"return"sv,
	};

	constexpr auto container_peek = std::array{
		"peek"sv,
		"return"sv,
	};

	constexpr auto container_contains = std::array{
		"contains"sv,
		"return"sv,
	};

	constexpr auto container_size = std::array{
		"size"sv,
		"return"sv,
	};

	constexpr auto container_empty = std::array{
		"size"sv,
		"not"sv,
		"return"sv,
	};

	constexpr auto container_at = std::array{
		"at"sv,
		"return"sv,
	};
	
	constexpr auto container_front = std::array{
		"front"sv,
		"return"sv,
	};
	
	constexpr auto container_back = std::array{
		"back"sv,
		"return"sv,
	};

	constexpr auto container_begin = std::array{
		"begin"sv,
		"return"sv,
	};

	constexpr auto container_end = std::array{
		"end"sv,
		"return"sv,
	};

	constexpr auto container_insert_back = std::array{
		"insert 2"sv,
	};


	constexpr auto container_insert_front = std::array{
		"insert 0"sv,
	};

	constexpr auto container_insert = std::array{
		"insert 1"sv,
	};

	constexpr auto container_remove_back = std::array{
		"remove 2"sv,
	};

	constexpr auto container_remove_front = std::array{
		"remove 0"sv,
	};
	
	constexpr auto container_remove = std::array{
		"remove 1"sv,
	};
}