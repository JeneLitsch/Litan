#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/iteration.hxx"

namespace ltn::vm::inst {
	void iter(VmCore & core) {
		auto ref = core.stack.pop();
		core.stack.push(iteration::wrap(ref, core.heap));
	}
}