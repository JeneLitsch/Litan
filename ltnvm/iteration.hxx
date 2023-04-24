#pragma once
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Heap.hxx"

namespace ltn::vm::iteration {
	Value wrap(const Value & iter_ref, Heap & heap);
	Value next(const Value & iter_ref, Heap & heap);
}