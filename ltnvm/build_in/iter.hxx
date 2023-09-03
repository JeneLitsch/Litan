#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in::iter {
	Value range(VMCore & core);
	Value next(VMCore & core);
	Value get(VMCore & core);
	Value move(VMCore & core);
	Value iter(VMCore & core);
	Value combined(VMCore & core);
	Value is_stop(VMCore & core);
	Value reversed(VMCore & core);
}