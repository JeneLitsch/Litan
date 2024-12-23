#pragma once
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"
#include "stdxx/float64_t.hxx"

// Implicit type conversions
namespace ltn::vm{
	class Heap;
}
namespace ltn::vm::convert {
	bool to_bool(const Value value, VMCore & core);
	std::int64_t to_int(const Value value);
	stx::float64_t to_float(const Value value);
	std::string to_string(Value value);
}