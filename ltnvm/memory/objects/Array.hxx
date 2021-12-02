#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	struct Array {
		std::vector<Value> arr;
		constexpr static std::string_view typeName = "Array";
	};
}