#pragma once
#include "ltn/variant.hxx"
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Heap.hxx"

namespace ltn::vm {
	Variant to_variant(const Value & value, Heap & heap);
}