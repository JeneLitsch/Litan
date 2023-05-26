#pragma once
#include "ltn/variant.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"

namespace ltn::vm {
	Value to_value(const Variant & variant, Heap & heap);
}