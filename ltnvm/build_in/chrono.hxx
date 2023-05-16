#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in::chrono {
	
	// Algorithm
	Value clock(VmCore & core);
	Value to_seconds(VmCore & core);
	Value to_milliseconds(VmCore & core);
}