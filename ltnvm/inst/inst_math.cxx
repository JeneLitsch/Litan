#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <cmath>
#include "ltnvm/MathFunctions.hxx"
#include "ltnvm/convert.hxx"
#include "ltnvm/Operations.hxx"

namespace ltn::vm::inst {
	#define FETCH\
		const auto r = core.reg.pop();\
		const auto l = core.reg.pop();



	void hypot(VmCore & core) {
		FETCH
		core.reg.push(std::hypot(
			convert::to_float(l),
			convert::to_float(r)));
	}


	void sqrt(VmCore & core) {
		const auto value = core.reg.pop();
		core.reg.push(std::sqrt(convert::to_float(value)));
	}


	void log(VmCore & core) {
		FETCH
		const auto result 
			= std::log(convert::to_float(l))
			/ std::log(convert::to_float(r));
		core.reg.push(result);
	}


	void ln(VmCore & core) {
		const auto value = core.reg.pop();
		core.reg.push(std::log(convert::to_float(value)));
	}



	


	

	#undef FETCH
}