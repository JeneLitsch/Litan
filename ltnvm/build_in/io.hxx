#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in::io {
	Value cout(VMCore & core);
	Value fout(VMCore & core);
	Value strout(VMCore & core);

	Value cin(VMCore & core);
	Value fin(VMCore & core);
	Value strin(VMCore & core);

	Value close_stream(VMCore & core);
	Value is_eof(VMCore & core);

	Value print(VMCore & core);

	Value read_str(VMCore & core);
	Value read_line(VMCore & core);
	Value read_bool(VMCore & core);
	Value read_char(VMCore & core);
	Value read_int(VMCore & core);
	Value read_float(VMCore & core);
	Value read_all(VMCore & core);

	Value set_fg_color(VMCore & core);
	Value set_bg_color(VMCore & core);
	Value reset_color(VMCore & core);

}