#pragma once
#include <string>

namespace ltn::c::compile::inst {
	std::string comment(std::string msg);
	std::string jumpmark(const std::string_view id);
	const std::string_view r3turn = "return\n";
	const std::string_view error = "error\n";
}