#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include <sstream>
namespace ltn::vm::inst {
	void capture(VmCore & core) {
		const auto var = core.stack.pop();
		const auto fxptr = core.stack.peek();
		if(is_fxptr(fxptr)) {
			auto & lambda = core.heap.read<FxPointer>(fxptr);
			lambda.captured.push_back(var);
		}
		else throw except::invalid_argument();
	}
}