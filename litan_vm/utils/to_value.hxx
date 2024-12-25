#pragma once
#include "litan_core/cxx_types.hxx"
#include "litan_vm/Value.hxx"
#include "litan_vm/Heap.hxx"

namespace ltn::vm {
	Value to_value(const Any & any, Heap & heap);
}