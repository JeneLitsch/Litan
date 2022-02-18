#include "compare.hxx"
#include "memory/Heap.hxx"
namespace ltn::vm {
	std::partial_ordering cmp(auto l, auto r) {
		using Promoted = decltype(l + r);
		return static_cast<Promoted>(l) <=> static_cast<Promoted>(r);
	}

	std::partial_ordering compareR(auto l, const Value r) {
		if(isBool(r))  return cmp(l, r.b);
		if(isChar(r))  return cmp(l, r.c);
		if(isInt(r))   return cmp(l, r.i);
		if(isFloat(r)) return cmp(l, r.f);
		return std::partial_ordering::unordered;
	} 

	std::partial_ordering compare(const Value l, const Value r, Heap & heap) {
		if(isBool(l))  return compareR(l.b, r);
		if(isChar(l))  return compareR(l.c, r);
		if(isInt(l))   return compareR(l.i, r);
		if(isFloat(l)) return compareR(l.f, r);
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