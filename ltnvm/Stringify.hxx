#pragma once
#include "memory/Value.hxx"
#include "memory/Heap.hxx"
namespace ltn::vm {
	std::string toString(const Value & value, Heap & heap);
}