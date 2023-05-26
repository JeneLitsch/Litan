#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include <cmath>
#include "ltnvm/utils/convert.hxx"

namespace ltn::vm::inst {
	#define FETCH\
		const auto r = core.stack.pop();\
		const auto l = core.stack.pop();
	#undef FETCH
}