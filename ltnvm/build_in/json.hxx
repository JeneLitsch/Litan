#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in::json {
	Value parse(VMCore & core);
	Value print(VMCore & core);
}