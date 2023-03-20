#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value close_stream(VmCore & core);
	Value is_eof(VmCore & core);

	Value print(VmCore & core);

	Value read_str(VmCore & core);
	Value read_line(VmCore & core);
	Value read_bool(VmCore & core);
	Value read_char(VmCore & core);
	Value read_int(VmCore & core);
	Value read_float(VmCore & core);
	Value read_all(VmCore & core);

	Value set_fg_color(VmCore & core);
	Value set_bg_color(VmCore & core);
	Value reset_color(VmCore & core);

}