#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	constexpr auto functional_invoke_2 = std::array{
		"invoke"sv,
		"return"sv,
	};

	constexpr auto functional_invoke_1 = std::array{
		"newarr 0"sv,
		"invoke"sv,
		"return"sv,
	};

	constexpr auto functional_external = std::array{
		"external"sv,
		"return"sv,
	};
}