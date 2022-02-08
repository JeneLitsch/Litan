#pragma once
#include <vector>
#include <utility>
#include "ltnvm/memory/Value.hxx"

namespace ltn::vm {
	struct Struct {
		using Members = std::vector<std::pair<std::uint64_t, Value>>;

		constexpr static std::string_view typeName = "Struct";
		
		Members members;
	
		auto clone() const {
			return *this;
		}
	};
	
}