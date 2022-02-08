#pragma once
#include <cstdint>
#include <string_view>

namespace ltn::vm {
	struct Range {
		constexpr static std::string_view typeName = "Range";
		
		std::uint64_t array;
		std::int64_t begin;
		std::int64_t end;
	
		auto clone() const {
			return *this;
		}
	};
	
}