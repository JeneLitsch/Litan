#pragma once
#include "ltn/variant.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"

namespace ltn::vm {
	Variant to_variant(const Value & value, Heap & heap);
}