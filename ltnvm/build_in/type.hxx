#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in::type {
	Value id(VmCore & core);
	Value clone(VmCore & core);
	Value is(VmCore & core);
	Value cast(VmCore & core);

	Value queue(VmCore & core);
	Value stack(VmCore & core);
	Value map(VmCore & core);
	Value strukt(VmCore & core);
}