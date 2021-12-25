#pragma once
#include <cstdint>

namespace ltn::c::compile {
	// Tracks, stores and resolves local variables  
	struct Variable {
		enum class Qualifier {
			CONST, MUTABLE,
		};
		std::uint64_t address;
		Qualifier qualifier;
	};

	bool isConst(const Variable & var);
	bool isMutable(const Variable & var);
}