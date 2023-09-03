#include "instructions.hxx"
#include "ltnvm/utils/cast.hxx"

namespace ltn::vm::inst {
	void cast_bool(VMCore & core) {
		const auto value = core.stack.pop();
		const auto b = cast::to_bool(value, core);
		core.stack.push(Value(b));
	}
}