#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in {
	Value arity(VMCore & core);
	Value invoke(VMCore & core);
	Value is_variadic(VMCore & core);
	Value noroutine(VMCore & core);
	Value is_noroutine(VMCore & core);
}