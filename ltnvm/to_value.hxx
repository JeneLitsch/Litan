#pragma once
#include "ltn/variant.hxx"
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Heap.hxx"

namespace ltn::vm {
	Value to_value(const Variant & variant, Heap & heap);
}