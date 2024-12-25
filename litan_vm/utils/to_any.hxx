#pragma once
#include "litan_core/cxx_types.hxx"
#include "litan_vm/Value.hxx"
#include "litan_vm/Heap.hxx"

namespace ltn::vm {
	Any to_any(const Value & value);
	Any to_any(const Value & value, Heap & heap);
}