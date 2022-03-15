#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	constexpr auto io_cout = std::array{
		"newout 0"sv,
		"return"sv,
	};

	constexpr auto io_fout = std::array{
		"newout 1"sv,
		"return"sv,
	};

	constexpr auto io_strout = std::array{
		"newout 2"sv,
		"return"sv,
	};

	constexpr auto io_print = std::array{
		"out"sv,
	};


	constexpr auto io_cin = std::array{
		"newin 0"sv,
		"return"sv,
	};

	constexpr auto io_fin = std::array{
		"newin 1"sv,
		"return"sv,
	};

	constexpr auto io_strin = std::array{
		"newin 2"sv,
		"return"sv,
	};

	constexpr auto io_read = std::array{
		"in_str"sv,
		"return"sv,
	};

	constexpr auto io_read_str = std::array{
		"in_str"sv,
		"return"sv,
	};

	constexpr auto io_readln = std::array{
		"in_line"sv,
		"return"sv,
	};

	constexpr auto io_read_bool = std::array{
		"in_bool"sv,
		"return"sv,
	};

	constexpr auto io_read_char = std::array{
		"in_char"sv,
		"return"sv,
	};

	constexpr auto io_read_int = std::array{
		"in_int"sv,
		"return"sv,
	};

	constexpr auto io_read_float = std::array{
		"in_float"sv,
		"return"sv,
	};

	constexpr auto io_read_all = std::array{
		"in_all"sv,
		"return"sv,
	};

	constexpr auto io_is_eof = std::array{
		"is_eof"sv,
		"return"sv,
	};

	constexpr auto io_is_good = std::array{
		"is_good"sv,
		"return"sv,
	};
}