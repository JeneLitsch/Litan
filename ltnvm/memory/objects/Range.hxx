#pragma once
#include <cstdint>
#include <string_view>

namespace ltn::vm {
	struct Range {
		std::uint64_t array;
		std::int64_t begin;
		std::int64_t end;
		constexpr static std::string_view typeName = "Range";
	};
	
}