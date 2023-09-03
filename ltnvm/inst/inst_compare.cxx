#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/calc_binary.hxx"
#include "ltnvm/utils/compare.hxx"
#include "ltnvm/utils/convert.hxx"

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



	void eql(VMCore & core) {
		FETCH
		return core.stack.push(value::boolean(compare(l, r, core) == 0));
	}



	void ueql(VMCore & core) {
		FETCH
		return core.stack.push(value::boolean(compare(l, r, core) != 0));
	}



	void lt(VMCore & core) {
		FETCH
		return core.stack.push(value::boolean(compare(l, r, core) < 0));
	}



	void gt(VMCore & core) {
		FETCH
		return core.stack.push(value::boolean(compare(l, r, core) > 0));
	}



	void smleql(VMCore & core) {
		FETCH
		return core.stack.push(value::boolean(compare(l, r, core) <= 0));
	}



	void bgreql(VMCore & core) {
		FETCH
		return core.stack.push(value::boolean(compare(l, r, core) >= 0));
	}



	void comp(VMCore & core) {
		FETCH
		const auto result = compare(l, r, core);
		return core.stack.push(eval_3_way(result));
	}

	#undef FETCH
}