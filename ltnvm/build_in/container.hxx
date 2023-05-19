#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value insert_front(VmCore & core);
	Value insert_back(VmCore & core);
	Value insert(VmCore & core);

	Value remove_front(VmCore & core);
	Value remove_back(VmCore & core);
	Value remove(VmCore & core);
}