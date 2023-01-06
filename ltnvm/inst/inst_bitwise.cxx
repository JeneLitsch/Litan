#include "instructions.hxx"
#include <cmath>
#include "ltnvm/type_check.hxx"
#include <sstream>
#include "ltnvm/Operations.hxx"
#include "ltnvm/calcBinary.hxx"
#include "ltnvm/convert.hxx"

#define FETCH\
	const auto r = core.reg.pop();\
	const auto l = core.reg.pop();

namespace ltn::vm::inst {
	void shift_l(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) << convert::to_int(r);
		return core.reg.push(Value{value});
	}



	void shift_r(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) >> convert::to_int(r);
		return core.reg.push(Value{value});
	}



	void bit_and(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) & convert::to_int(r);
		return core.reg.push(Value{value});
	}



	void bit_or(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) | convert::to_int(r);
		return core.reg.push(Value{value});
	}

	

	void bit_xor(VmCore & core) {
		FETCH
		const auto value = convert::to_int(l) ^ convert::to_int(r);
		return core.reg.push(Value{value});
	}



	void bit_not(VmCore & core) {
		const auto x = core.reg.pop();
		return core.reg.push(Value{~convert::to_int(x)});
	}
}
#undef FETCH