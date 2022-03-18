#pragma once
#include "memory/Value.hxx"
#include "memory/Heap.hxx"
#include "ltn/float64_t.hxx"

// Implicit type conversions
namespace ltn::vm{
	class Heap;
}
namespace ltn::vm::convert {
	bool to_bool(const Value value);
	std::int64_t to_int(const Value value);
	stx::float64_t to_float(const Value value);
	char to_char(const Value value);
	std::string to_string(Value value, Heap & heap);
}