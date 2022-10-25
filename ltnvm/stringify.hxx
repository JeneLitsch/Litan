#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm {
	std::string stringify(const Value & value, Heap & heap);
}