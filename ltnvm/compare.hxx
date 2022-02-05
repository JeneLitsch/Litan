#pragma once
#include <stdexcept>
#include "memory/Value.hxx"
#include "TypeCheck.hxx"
namespace ltn::vm {
	std::partial_ordering compare(const Value l, const Value r, Heap & heap) {
		if(isInt(l) && isInt(r)) return l.i <=> r.i;
		if(isInt(l) && isFloat(r)) return static_cast<double>(l.i) <=> r.f;
		if(isFloat(l) && isInt(r))  return l.f <=> static_cast<double>(r.i);
		if(isFloat(l) && isFloat(r)) return l.f <=>  r.f;
		if(l.type == r.type) {
			if(isStr(l)) {
				const auto & strL = heap.read<String>(l.u);
				const auto & strR = heap.read<String>(r.u);
				return strL.str <=> strR.str;
			}
			return std::partial_ordering::equivalent;
		}
		return l.type <=> r.type;
	}
}