#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile {
	constexpr auto type_typeid = std::array{
		"typeid"sv,
		"return"sv,
	};

	constexpr auto type_clone = std::array{
		"clone"sv,
		"return"sv,
	};
}