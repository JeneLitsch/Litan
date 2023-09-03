#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm::inst {
	void iter(VMCore & core) {
		auto ref = core.stack.pop();
		core.stack.push(iterator::wrap(ref, core.heap));
	}
}