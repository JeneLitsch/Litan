#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value sort_desc(VmCore & core);
	Value sort_ascn(VmCore & core);
	Value is_sorted_ascn(VmCore & core);
	Value is_sorted_desc(VmCore & core);
	Value find(VmCore & core);
	Value copy_front(VmCore & core);
	Value copy_back(VmCore & core);
	Value fill(VmCore & core);
	Value reverse(VmCore & core);
}