#pragma once
#include "litan_vm/VMCore.hxx"

namespace ltn::vm::build_in::type {
	Value id(VMCore & core);
	Value clone(VMCore & core);
	Value is(VMCore & core);
	Value cast(VMCore & core);

	Value queue(VMCore & core);
	Value stack(VMCore & core);
	Value map(VMCore & core);
	Value strukt(VMCore & core);
}