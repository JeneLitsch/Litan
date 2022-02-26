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

	bool is_const(const Variable & var);
	bool is_mutable(const Variable & var);
}