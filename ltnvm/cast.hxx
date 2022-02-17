#pragma once
#include "memory/Value.hxx"
#include "memory/Heap.hxx"
namespace ltn::vm::cast {
	std::string to_string(Value value, Heap & heap);
	std::int64_t to_int(Value value, Heap & heap);
	double to_float(Value value, Heap & heap);
	bool to_bool(Value value);
	char to_char(Value value);
}