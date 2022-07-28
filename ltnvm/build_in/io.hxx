#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value set_fg_color(VmCore & core);
	Value set_bg_color(VmCore & core);
	Value reset_color(VmCore & core);
}