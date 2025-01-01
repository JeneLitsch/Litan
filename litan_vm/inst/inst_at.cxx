#include "instructions.hxx"
#include "litan_vm/utils/index.hxx"
#include "litan_vm/utils/container.hxx"

namespace ltn::vm::inst {
	void at(VMCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		core.stack.push(get_element_from_container(ref, key));
	}
}