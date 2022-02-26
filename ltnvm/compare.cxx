#include "compare.hxx"
#include "memory/Heap.hxx"
namespace ltn::vm {
	std::partial_ordering cmp(auto l, auto r) {
		using Promoted = decltype(l + r);
		return static_cast<Promoted>(l) <=> static_cast<Promoted>(r);
	}


	#define COMPARE_R(l) {\
		if(is_bool(r))  return cmp(l, r.b);\
		if(is_char(r))  return cmp(l, r.c);\
		if(is_int(r))   return cmp(l, r.i);\
		if(is_float(r)) return cmp(l, r.f);\
	}

	std::partial_ordering compare(const Value l, const Value r, Heap & heap) {
		if(is_bool(l))  COMPARE_R(l.b);
		if(is_char(l))  COMPARE_R(l.c);
		if(is_int(l))   COMPARE_R(l.i);
		if(is_float(l)) COMPARE_R(l.f);
		if(l.type == r.type) {
			if(is_string(l)) {
				const auto & strL = heap.read<String>(l.u).get();
				const auto & strR = heap.read<String>(r.u).get();
				return strL <=> strR;
			}
			if(is_array(l)) {
				const auto & arrL = heap.read<Array>(l.u).get();
				const auto & arrR = heap.read<Array>(r.u).get();
				if(arrL.size() != arrR.size()) {
					return arrL.size() <=> arrR.size();
				}
				for(std::size_t i = 0; i < arrL.size(); i++) {
					const auto & elemL = arrL[i];
					const auto & elemR = arrR[i];
					const auto & comp = compare(elemL, elemR, heap);
					if(comp != 0) {
						return comp;
					}
				}
				return std::partial_ordering::equivalent;
			}
			return std::partial_ordering::equivalent;
		}
		return l.type <=> r.type;
	}
}