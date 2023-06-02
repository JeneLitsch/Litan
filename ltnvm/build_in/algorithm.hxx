#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	
	// Algorithm
	Value sort_desc(VmCore & core);
	Value sort_ascn(VmCore & core);
	Value is_sorted_ascn(VmCore & core);
	Value is_sorted_desc(VmCore & core);
	Value find(VmCore & core);
	Value fill(VmCore & core);
	Value reverse(VmCore & core);
	Value reduce_l_2(VmCore & core);
	Value reduce_l_3(VmCore & core);
}