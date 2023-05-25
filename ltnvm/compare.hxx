#pragma once
#include <stdexcept>
#include "memory/Value.hxx"
#include "type_check.hxx"
namespace ltn::vm {
	class VmCore;
	std::partial_ordering compare(const Value l, const Value r, VmCore & core);
	std::partial_ordering num_compare(const Value l, const Value r);
}