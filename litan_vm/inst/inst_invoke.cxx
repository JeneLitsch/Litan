#include "instructions.hxx"
#include "litan_vm/utils/function.hxx"

namespace ltn::vm::inst {
	void invoke(VMCore & core) {
		const auto arity = core.fetch_byte();
		const auto ref_fx = core.stack.pop();

		invoke_function(core, ref_fx, arity);
	}
}