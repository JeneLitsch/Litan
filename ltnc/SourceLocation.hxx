#pragma once
#include <cstdint>
#include <string>

namespace ltn::c {
	struct SourceLocation {
		std::uint64_t line = 0;
		std::string sourcename = "";
	};


	struct ArgumentLocation {
		SourceLocation source_location;
		std::uint64_t index;
	};
}