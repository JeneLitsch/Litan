#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/calcBinary.hxx"
#include "ltnvm/Operations.hxx"
#include "ltnvm/compare.hxx"
#include "ltnvm/convert.hxx"

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
		const auto r = core.stack.pop();\
		const auto l = core.stack.pop();



	void eql(VmCore & core) {
		FETCH
		return core.stack.push(compare(l, r, core.heap) == 0);
	}



	void ueql(VmCore & core) {
		FETCH
		return core.stack.push(compare(l, r, core.heap) != 0);
	}



	void sml(VmCore & core) {
		FETCH
		return core.stack.push(compare(l, r, core.heap) < 0);
	}



	void bgr(VmCore & core) {
		FETCH
		return core.stack.push(compare(l, r, core.heap) > 0);
	}



	void smleql(VmCore & core) {
		FETCH
		return core.stack.push(compare(l, r, core.heap) <= 0);
	}



	void bgreql(VmCore & core) {
		FETCH
		return core.stack.push(compare(l, r, core.heap) >= 0);
	}



	void comp(VmCore & core) {
		FETCH
		const auto result = compare(l, r, core.heap);
		return core.stack.push(eval_3_way(result));
	}



	void between(VmCore & core) {
		const auto to = core.stack.pop(); 
		const auto from = core.stack.pop(); 
		const auto i = core.stack.pop();

		const auto from_is_less = num_compare(from, to) < 0;
		const auto min = from_is_less ? from : to;
		const auto max = from_is_less ? to : from;

		const bool is_in_range = 
			num_compare(i, min) < 0 ||
			num_compare(i, max) > 0;
		
		core.stack.push(value::boolean(is_in_range));
	}

	#undef FETCH
}