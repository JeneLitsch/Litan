#pragma once
#include <cstdint>
#include <string>

namespace ltn::c {
	struct SourceLocation {
		std::size_t line = 0;
		std::string sourcename = "";
	};
}