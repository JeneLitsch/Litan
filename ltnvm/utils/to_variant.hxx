#pragma once
#include "ltn/cxx_types.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"

namespace ltn::vm {
	Any to_variant(const Value & value);
	Any to_variant(const Value & value, Heap & heap);
}