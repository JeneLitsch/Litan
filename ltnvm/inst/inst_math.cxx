#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <cmath>
#include "ltnvm/MathFunctions.hxx"
#include "ltnvm/convert.hxx"
#include "ltnvm/Operations.hxx"

namespace ltn::vm::inst {
	#define FETCH\
		const auto r = core.stack.pop();\
		const auto l = core.stack.pop();
	#undef FETCH
}