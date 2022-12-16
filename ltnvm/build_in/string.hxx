#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value to_string(VmCore & core);
	Value split_string(VmCore & core);
	Value join_string(VmCore & core);
	Value parse_bool(VmCore & core);
	Value parse_char(VmCore & core);
	Value parse_int(VmCore & core);
	Value parse_float(VmCore & core);
}