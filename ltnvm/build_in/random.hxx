#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value split(VmCore & core);
	Value rand(VmCore & core);
	Value rand_int(VmCore & core);
	Value rand_float(VmCore & core);
}