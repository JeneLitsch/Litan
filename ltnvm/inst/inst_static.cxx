#include "instructions.hxx"

namespace ltn::vm::inst {
	void static_read(VMCore & core) {
		const auto id = core.fetch_uint();
		core.stack.push(core.stack.read_absolute(id));
	}



	void static_write(VMCore & core) {
		const auto id = core.fetch_uint();
		const auto value = core.stack.pop();
		core.stack.write_absolute(id, value);
	}
}