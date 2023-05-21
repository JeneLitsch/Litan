#include "compare.hxx"
#include "memory/Heap.hxx"
#include "Exception.hxx"
namespace ltn::vm {
	namespace {
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

		std::partial_ordering compare_impl(const Value l, const Value r, Heap & heap) {
			if(is_bool(l))  COMPARE_R(l.b);
			if(is_char(l))  COMPARE_R(l.c);
			if(is_int(l))   COMPARE_R(l.i);
			if(is_float(l)) COMPARE_R(l.f);
			if(l.type == r.type) {
				if(is_string(l)) {
					const auto & strL = heap.read<String>(l.u);
					const auto & strR = heap.read<String>(r.u);
					return strL <=> strR;
				}
				if(is_array(l) || is_tuple(l)) {
					const auto & arrL = heap.read<Array>(l.u);
					const auto & arrR = heap.read<Array>(r.u);
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
				if(is_stack(l) || is_queue(l)) {
					const auto & deq_l = heap.read<Deque>(l.u);
					const auto & deq_r = heap.read<Deque>(r.u);
					if(deq_l.size() != deq_r.size()) {
						return deq_l.size() <=> deq_r.size();
					}
					for(std::size_t i = 0; i < deq_l.size(); i++) {
						const auto & elemL = deq_l[i];
						const auto & elemR = deq_r[i];
						const auto & comp = compare(elemL, elemR, heap);
						if(comp != 0) {
							return comp;
						}
					}
					return std::partial_ordering::equivalent;
				}
				if(is_type(l) || is_type(l)) {
					return l.u <=> r.u;
				}
				return std::partial_ordering::equivalent;
			}
			return l.type <=> r.type;
		}
	}

	
	
	std::partial_ordering num_compare(const Value l, const Value r) {
		if(is_bool(l))  COMPARE_R(l.b);
		if(is_char(l))  COMPARE_R(l.c);
		if(is_int(l))   COMPARE_R(l.i);
		if(is_float(l)) COMPARE_R(l.f);
		throw Exception{ Exception::Type::GENERIC_ERROR, "Invalid comparison"};
	}

	
	
	std::partial_ordering compare(const Value l, const Value r, Heap & heap) {
		const auto result = compare_impl(l, r, heap);
		if(result == std::partial_ordering::unordered) {
			throw Exception{ Exception::Type::GENERIC_ERROR, "Invalid comparison"};
		}
		return result;
	}
}