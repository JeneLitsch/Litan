#include "instructions.hxx"
#include "type_check.hxx"
#include "calcBinary.hxx"
#include "Operations.hxx"
#include "compare.hxx"
#include "convert.hxx"

namespace ltn::vm::inst {

	
	namespace {
		Value eval_3_way(std::partial_ordering order) {
			if(order == 0) return value::integer(0);
			if(order <  0) return value::integer(-1);
			if(order >  0) return value::integer(1);
			throw except::invalid_operands(); 
		}
	}
	
	#define FETCH\
		const auto r = core.reg.pop();\
		const auto l = core.reg.pop();

	void eql(VmCore & core) {
		FETCH
		return core.reg.push(compare(l, r, core.heap) == 0);
	}
	void ueql(VmCore & core) {
		FETCH
		return core.reg.push(compare(l, r, core.heap) != 0);
	}
	void sml(VmCore & core) {
		FETCH
		return core.reg.push(compare(l, r, core.heap) < 0);
	}
	void bgr(VmCore & core) {
		FETCH
		return core.reg.push(compare(l, r, core.heap) > 0);
	}
	void smleql(VmCore & core) {
		FETCH
		return core.reg.push(compare(l, r, core.heap) <= 0);
	}
	void bgreql(VmCore & core) {
		FETCH
		return core.reg.push(compare(l, r, core.heap) >= 0);
	}
	void comp(VmCore & core) {
		FETCH
		const auto result = compare(l, r, core.heap);
		return core.reg.push(eval_3_way(result));
	}

	void approx(VmCore & core) {
		static constexpr stx::float64_t max = std::numeric_limits<stx::float64_t>::max();
		static constexpr stx::float64_t eps = std::numeric_limits<stx::float64_t>::epsilon();
		FETCH
		if(is_numeric(l) || is_numeric(r)) {
			const stx::float64_t r_float = convert::to_float(r);
			const stx::float64_t l_float = convert::to_float(l);
			const stx::float64_t diff = std::abs(l_float - r_float);
			const stx::float64_t norm = std::min((l_float + r_float), max);
			const bool is_sameish = diff < (norm * eps);
			return core.reg.push(value::boolean(is_sameish)); 
		}
		else {
			const bool is_sameish = compare(l, r, core.heap) == 0;
			return core.reg.push(value::boolean(is_sameish)); 
		}
	}

	void between(VmCore & core) {
		const auto to = core.reg.pop(); 
		const auto from = core.reg.pop(); 
		const auto i = core.reg.pop();

		const auto from_is_less = num_compare(from, to) < 0;
		const auto min = from_is_less ? from : to;
		const auto max = from_is_less ? to : from;

		const bool is_in_range = 
			num_compare(i, min) <= 0 ||
			num_compare(i, max) > 0;
		
		core.reg.push(value::boolean(is_in_range));
	}

	#undef FETCH
}