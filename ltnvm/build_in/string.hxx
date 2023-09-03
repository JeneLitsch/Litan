#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in {
	Value to_string(VMCore & core);
	Value split_string(VMCore & core);
	Value parse_bool(VMCore & core);
	Value parse_char(VMCore & core);
	Value parse_int(VMCore & core);
	Value parse_float(VMCore & core);
}