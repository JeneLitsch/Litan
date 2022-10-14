#pragma once
#include <cstdint>
#include "ltnc/type/Type.hxx"

namespace ltn::c {
	// Tracks, stores and resolves local variables  
	struct Variable {
		std::uint64_t address;
		type::Type type;
	};
}