#pragma once
#include "ltn/cxx_types.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"

namespace ltn::vm {
	Any to_any(const Value & value);
	Any to_any(const Value & value, Heap & heap);
}