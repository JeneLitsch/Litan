#include "instructions.hxx"
#include "litan_vm/utils/type_check.hxx"

namespace ltn::vm::inst {
	void iter(VMCore & core) {
		auto ref = core.stack.pop();
		core.stack.push(iterator::wrap(ref, core));
	}
}