#pragma once
#include "memory/Value.hxx"
#include "memory/Heap.hxx"

// Implicit type conversions
namespace ltn::vm::convert {
	bool to_bool(const Value);
	std::int64_t to_int(const Value);
	double to_float(const Value);
	char to_char(const Value);
	std::string to_string(Value value, Heap & heap);
}