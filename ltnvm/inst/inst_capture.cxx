#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <sstream>
namespace ltn::vm::inst {
	void capture(VmCore & core) {
		const auto var = core.reg.pop();
		const auto fxptr = core.reg.peek();
		if(is_fxptr(fxptr)) {
			auto & lambda = core.heap.read<FxPointer>(fxptr.u);
			lambda.captured.push_back(var);
		}
		else throw except::invalid_argument();
	}
}