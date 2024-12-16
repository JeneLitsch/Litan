#pragma once
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"
#include "stdxx/float64_t.hxx"

// Explicit type conversions
namespace ltn::vm::cast {
	std::string to_string(Value value);
	Array to_array(Value value);
	std::int64_t to_int(Value value);
	stx::float64_t to_float(Value value);
	bool to_bool(Value value, VMCore & core);
	char to_char(Value value);
}