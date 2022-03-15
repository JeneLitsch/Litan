#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile {
	constexpr auto chrono_clock = std::array{
		"newclock"sv,
		"return"sv,
	};

	constexpr auto chrono_to_seconds = std::array{
		"cast_float"sv,
		"return"sv,
	};

	constexpr auto chrono_to_milliseconds = std::array{
		"cast_float"sv,
		"newf 1000.0"sv,
		"mlt"sv,
		"return"sv,
	};
}