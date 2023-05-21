#include "instructions.hxx"
#include "ltnvm/cast.hxx"

namespace ltn::vm::inst {
	void cast_bool(VmCore & core) {
		const auto value = core.stack.pop();
		const auto b = cast::to_bool(value);
		core.stack.push(Value(b));
	}
}