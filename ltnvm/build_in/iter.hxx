#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in::iter {
	Value range(VmCore & core);
	Value next(VmCore & core);
	Value iter(VmCore & core);
}