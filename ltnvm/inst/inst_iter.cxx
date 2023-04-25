#include "instructions.hxx"
#include "ltnvm/type_check.hxx"

namespace ltn::vm::inst {
	void iter(VmCore & core) {
		auto ref = core.stack.pop();
		core.stack.push(iterator::wrap(ref, core.heap));
	}
}