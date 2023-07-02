#pragma once
#include <vector>
#include <deque>
#include "Value.hxx"
#include "objects/objects.hxx"

namespace ltn::vm::gc {
	void mark(const Value & value);
	void mark(const std::vector<Value> & values);
	void mark(const std::deque<Value> & values);

	std::uint64_t sweep(std::unique_ptr<Object> & start);
}