#pragma once
#include <cstdint>

namespace ltn::c {
	// Tracks, stores and resolves local variables  
	struct Variable {
		std::uint64_t address;
	};
}