#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in {
	Value push(VMCore & core);
	Value pop(VMCore & core);
	Value peek(VMCore & core);
	Value contains(VMCore & core);
	Value size(VMCore & core);
	Value empty(VMCore & core);
	Value at(VMCore & core);
	Value front(VMCore & core);
	Value back(VMCore & core);

	Value insert_front(VMCore & core);
	Value insert_back(VMCore & core);
	Value insert(VMCore & core);

	Value remove_front(VMCore & core);
	Value remove_back(VMCore & core);
	Value remove(VMCore & core);
}