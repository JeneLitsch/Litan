#pragma once
#include "litan_vm/VMCore.hxx"

namespace ltn::vm::build_in::random {
	Value mersenne_0(VMCore & core);
	Value mersenne_1(VMCore & core);

	Value split(VMCore & core);
	Value rand(VMCore & core);
	Value rand_int(VMCore & core);
	Value rand_float(VMCore & core);
}