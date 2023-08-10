#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value insert_back_string(VmCore & core, Value ref, Value elem);

	Value push(VmCore & core);
	Value pop(VmCore & core);
	Value peek(VmCore & core);
	Value contains(VmCore & core);
	Value size(VmCore & core);
	Value empty(VmCore & core);
	Value at(VmCore & core);
	Value front(VmCore & core);
	Value back(VmCore & core);

	Value insert_front(VmCore & core);
	Value insert_back(VmCore & core);
	Value insert(VmCore & core);

	Value remove_front(VmCore & core);
	Value remove_back(VmCore & core);
	Value remove(VmCore & core);
}