#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in::iter {
	Value range(VmCore & core);
	Value next(VmCore & core);
	Value get(VmCore & core);
	Value move(VmCore & core);
	Value iter(VmCore & core);
	Value is_stop(VmCore & core);
}