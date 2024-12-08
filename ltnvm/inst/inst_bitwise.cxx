#include <sstream>
#include <cmath>
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/convert.hxx"

#define FETCH\
	const auto r = core.stack.pop();\
	const auto l = core.stack.pop();

namespace ltn::vm::inst {
	void shift_l(VMCore & core) {
		FETCH
		const auto value = convert::to_int(l) << convert::to_int(r);
		return core.stack.push(value::deduce(value));
	}



	void shift_r(VMCore & core) {
		FETCH
		const auto value = convert::to_int(l) >> convert::to_int(r);
		return core.stack.push(value::deduce(value));
	}



	void bit_and(VMCore & core) {
		FETCH
		const auto value = convert::to_int(l) & convert::to_int(r);
		return core.stack.push(value::deduce(value));
	}



	void bit_or(VMCore & core) {
		FETCH
		const auto value = convert::to_int(l) | convert::to_int(r);
		return core.stack.push(value::deduce(value));
	}

	

	void bit_xor(VMCore & core) {
		FETCH
		const auto value = convert::to_int(l) ^ convert::to_int(r);
		return core.stack.push(value::deduce(value));
	}



	void bit_not(VMCore & core) {
		const auto x = core.stack.pop();
		return core.stack.push(value::deduce(~convert::to_int(x)));
	}
}
#undef FETCH