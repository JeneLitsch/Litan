#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	void sort_desc(VmCore & core);
	void sort_ascn(VmCore & core);
	void is_sorted_ascn(VmCore & core);
	void is_sorted_desc(VmCore & core);
	void find(VmCore & core);
	void copy_front(VmCore & core);
	void copy_back(VmCore & core);
	void fill(VmCore & core);
	void reverse(VmCore & core);
}