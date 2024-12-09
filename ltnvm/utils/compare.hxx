#pragma once
#include <stdexcept>
#include "ltnvm/Value.hxx"
#include "type_check.hxx"
namespace ltn::vm {
	struct VMCore;
	std::partial_ordering compare(const Value l, const Value r, VMCore & core);
	std::partial_ordering strict_compare(const Value l, const Value r, VMCore & core);
	std::partial_ordering num_compare(const Value l, const Value r);
}