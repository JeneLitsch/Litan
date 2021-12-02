#pragma once
#include <string>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	struct String {
		std::string str;
		constexpr static std::string_view typeName = "String";
	};
}