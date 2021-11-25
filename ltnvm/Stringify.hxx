#pragma once
#include "Value.hxx"
#include "Heap.hxx"
namespace ltn::vm {
	std::string toString(const Value & value, Heap & heap);
}