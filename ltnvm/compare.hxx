#pragma once
#include <stdexcept>
#include "memory/Value.hxx"
#include "TypeCheck.hxx"
namespace ltn::vm {
	std::partial_ordering compare(const Value l, const Value r) {
		if(isInt(l) && isInt(r)) return l.i <=> r.i;
		if(isInt(l) && isFloat(r)) return static_cast<double>(l.i) <=> r.f;
		if(isFloat(l) && isInt(r))  return l.f <=> static_cast<double>(r.i);
		if(isFloat(l) && isFloat(r)) return l.f <=>  r.f;
		throw std::runtime_error{"Cannot compare"};
	}
}