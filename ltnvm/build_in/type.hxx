#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in::type {
	Value id(VmCore & core);
	Value clone(VmCore & core);
}