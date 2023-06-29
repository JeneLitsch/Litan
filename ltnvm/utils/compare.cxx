#include "ltnvm/utils/compare.hxx"
#include "ltnvm/Heap.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/special_member.hxx"
#include "ltnvm/VmCore.hxx"

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

		std::partial_ordering compare_impl(const Value l, const Value r, VmCore & core) {
			if(is_bool(l))  COMPARE_R(l.b);
			if(is_char(l))  COMPARE_R(l.c);
			if(is_int(l))   COMPARE_R(l.i);
			if(is_float(l)) COMPARE_R(l.f);
			if(l.type == r.type) {
				if(is_string(l)) {
					const auto & strL = core.heap.read<String>(l);
					const auto & strR = core.heap.read<String>(r);
					return strL.data <=> strR.data;
				}
				if(is_array(l) || is_tuple(l)) {
					const auto & arrL = core.heap.read<Array>(l);
					const auto & arrR = core.heap.read<Array>(r);
					if(arrL.data.size() != arrR.data.size()) {
						return arrL.data.size() <=> arrR.data.size();
					}
					for(std::size_t i = 0; i < arrL.data.size(); i++) {
						const auto & elemL = arrL.data[i];
						const auto & elemR = arrR.data[i];
						const auto & comp = compare(elemL, elemR, core);
						if(comp != 0) {
							return comp;
						}
					}
					return std::partial_ordering::equivalent;
				}
				if(is_stack(l) || is_queue(l)) {
					const auto & deq_l = core.heap.read<Deque>(l);
					const auto & deq_r = core.heap.read<Deque>(r);
					if(deq_l.data.size() != deq_r.data.size()) {
						return deq_l.data.size() <=> deq_r.data.size();
					}
					for(std::size_t i = 0; i < deq_l.data.size(); i++) {
						const auto & elemL = deq_l.data[i];
						const auto & elemR = deq_r.data[i];
						const auto & comp = compare(elemL, elemR, core);
						if(comp != 0) {
							return comp;
						}
					}
					return std::partial_ordering::equivalent;
				}
				if(is_type(l) || is_type(l)) {
					return l.u <=> r.u;
				}
				if(is_struct(l)) {
					auto & strukt = core.heap.read<Struct>(l);
					auto comparator = find_special_member<MemberCode::CMP>(strukt);
					if(comparator) {
						auto ordering = run_special_member(core, *comparator, l, r);
						if(is_int(ordering)) {
							if(ordering.i == 0) return std::partial_ordering::equivalent;
							if(ordering.i < 0) return std::partial_ordering::less;
							if(ordering.i > 0) return std::partial_ordering::greater;
						}
						return std::partial_ordering::unordered;
					}
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

	
	
	std::partial_ordering compare(const Value l, const Value r, VmCore & core) {
		const auto result = compare_impl(l, r, core);
		if(result == std::partial_ordering::unordered) {
			throw Exception{ Exception::Type::GENERIC_ERROR, "Invalid comparison"};
		}
		return result;
	}
}