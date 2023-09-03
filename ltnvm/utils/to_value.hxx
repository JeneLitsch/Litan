#pragma once
#include "ltn/cxx_types.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"

namespace ltn::vm {
	Value to_value(const Any & any, Heap & heap);
}