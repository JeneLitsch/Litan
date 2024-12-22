#include "ltnvm/utils/compare.hxx"
#include "ltnvm/Heap.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/special_member.hxx"
#include "ltnvm/VMCore.hxx"

namespace ltn::vm {
	std::partial_ordering object_compare(const Value l, const Value r, VMCore & core);
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

		std::partial_ordering compare_impl(const Value l, const Value r, VMCore & core) {
			if(is_bool(l))  COMPARE_R(l.b);
			if(is_char(l))  COMPARE_R(l.c);
			if(is_int(l))   COMPARE_R(l.i);
			if(is_float(l)) COMPARE_R(l.f);
			if(l.type == r.type) {
				return object_compare(l, r, core);
			}
			else {
				return l.type <=> r.type;
			}
		}
	}

	
	
	
	std::partial_ordering num_compare(const Value l, const Value r) {
		if(is_bool(l))  COMPARE_R(l.b);
		if(is_char(l))  COMPARE_R(l.c);
		if(is_int(l))   COMPARE_R(l.i);
		if(is_float(l)) COMPARE_R(l.f);
		throw Exception{ Exception::Type::GENERIC_ERROR, "Invalid comparison"};
	}



	inline std::partial_ordering object_compare(const Value l, const Value r, VMCore & core)  {
		if(is_string(l)) {
			const auto & strL = *value::as<String>(l);
			const auto & strR = *value::as<String>(r);
			return strL <=> strR;
		}
		if(is_array(l) || is_tuple(l)) {
			const auto & arrL = *value::as<Contiguous>(l);
			const auto & arrR = *value::as<Contiguous>(r);
			if(arrL.size() != arrR.size()) {
				return arrL.size() <=> arrR.size();
			}
			for(std::int64_t i = 0; i < std::ssize(arrL); i++) {
				const auto & elemL = arrL.unsafe_at(i);
				const auto & elemR = arrR.unsafe_at(i);
				const auto & comp = compare(elemL, elemR, core);
				if(comp != 0) {
					return comp;
				}
			}
			return std::partial_ordering::equivalent;
		}
		if(is_stack(l) || is_queue(l)) {
			const auto & deq_l = *value::as<Segmented>(l);
			const auto & deq_r = *value::as<Segmented>(r);
			if(deq_l.size() != deq_r.size()) {
				return deq_l.size() <=> deq_r.size();
			}
			for(std::int64_t i = 0; i < std::ssize(deq_l); i++) {
				const auto & elemL = deq_l.unsafe_at(i);
				const auto & elemR = deq_r.unsafe_at(i);
				const auto & comp = compare(elemL, elemR, core);
				if(comp != 0) {
					return comp;
				}
			}
			return std::partial_ordering::equivalent;
		}
		if(is_type(l)) {
			return l.obj_type <=> r.obj_type;
		}
		if(is_struct(l)) {
			auto & strukt = *value::as<Struct>(l);
			auto comparator = find_special_member<ReservedMemberCode::OPERATOR_CMP>(strukt);
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
		if(is_map(l) && is_map(r)) {
			const Map * map_l = value::as<Map>(l);
			const Map * map_r = value::as<Map>(r);
			if (map_l == map_r) {
				return std::partial_ordering::equivalent;
			}
			if(std::size(*map_l) != std::size(*map_r)) {
				return std::size(*map_l) <=> std::size(*map_r);
			}
			else {
				auto end_l = map_l->end();
				auto end_r = map_l->end();
				auto iter_l = map_l->begin();
				auto iter_r = map_l->begin();
				while(iter_l != end_l && end_r != end_r) {
					auto key_result = compare(iter_l->first, iter_r->first, core);
					if (key_result != 0) {
						return key_result;
					}
					auto value_result = compare(iter_l->second, iter_r->second, core);
					if (value_result != 0) {
						return value_result;
					}
				}
				return std::partial_ordering::equivalent;
			}
		}
		return std::partial_ordering::equivalent;
	
	}

	
	
	std::partial_ordering compare(const Value l, const Value r, VMCore & core) {
		const auto result = compare_impl(l, r, core);
		if(result == std::partial_ordering::unordered) {
			throw Exception{ Exception::Type::GENERIC_ERROR, "Invalid comparison"};
		}
		return result;
	}



	std::partial_ordering strict_compare(const Value l, const Value r, VMCore & core) {
		if (l.type == r.type) {
			if(is_bool(l))  return l.b <=> r.b;
			if(is_char(l))  return l.c <=> r.c;
			if(is_int(l))   return l.i <=> r.i;
			if(is_float(l)) return l.f <=> r.f;
			return object_compare(l, r, core);
		}
		else {
			return l.type <=> r.type;
		}

	}
}