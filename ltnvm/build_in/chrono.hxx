#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in::chrono {
	
	// Algorithm
	Value clock(VMCore & core);
	Value to_seconds(VMCore & core);
	Value to_milliseconds(VMCore & core);
}