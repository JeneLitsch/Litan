#pragma once
#include <stdexcept>
#include "memory/Value.hxx"
#include "type_check.hxx"
namespace ltn::vm {
	class Heap;
	std::partial_ordering compare(const Value l, const Value r, Heap & heap);
}