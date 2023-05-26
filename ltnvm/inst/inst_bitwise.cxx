#include <sstream>
#include <cmath>
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/convert.hxx"

#define FETCH\
	const auto r = core.stack.pop();\
	const auto l = core.stack.pop();

namespace ltn::vm::inst {
	void shift_l(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) << convert::to_int(r);
		return core.stack.push(Value{value});
	}



	void shift_r(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) >> convert::to_int(r);
		return core.stack.push(Value{value});
	}



	void bit_and(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) & convert::to_int(r);
		return core.stack.push(Value{value});
	}



	void bit_or(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) | convert::to_int(r);
		return core.stack.push(Value{value});
	}

	

	void bit_xor(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) ^ convert::to_int(r);
		return core.stack.push(Value{value});
	}



	void bit_not(VmCore & core) {
		const auto x = core.stack.pop();
		return core.stack.push(Value{~convert::to_int(x)});
	}
}
#undef FETCH