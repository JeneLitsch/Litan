#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in {
	
	// Algorithm
	Value sort_desc(VMCore & core);
	Value sort_ascn(VMCore & core);
	Value is_sorted_ascn(VMCore & core);
	Value is_sorted_desc(VMCore & core);
	Value find(VMCore & core);
	Value fill(VMCore & core);
	Value reverse(VMCore & core);
	Value reduce_l_2(VMCore & core);
	Value reduce_l_3(VMCore & core);
}