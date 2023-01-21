#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value lib_open(VmCore & core);
	Value lib_close(VmCore & core);
	Value lib_get_fx(VmCore & core);
}