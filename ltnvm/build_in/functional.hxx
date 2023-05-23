#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value arity(VmCore & core);
	Value invoke(VmCore & core);
	Value is_variadic(VmCore & core);
}