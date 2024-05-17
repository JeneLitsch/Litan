#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/index.hxx"

namespace ltn::vm::inst {
	void scrap(VMCore & core) {
		core.stack.pop();
	}



	void duplicate(VMCore & core) {
		core.stack.push(core.stack.peek());
	}



	void read_x(VMCore & core) {
		const auto address = core.fetch_uint();
		const auto value = core.stack.read(address);
		core.stack.push(value);
	}



	void write_x(VMCore & core) {
		const auto address = core.fetch_uint();
		const auto value = core.stack.pop();
		core.stack.write(address, value);
	}



	void swap(VMCore & core) {
		const auto a = core.stack.pop();
		const auto b = core.stack.pop();
		core.stack.push(a);
		core.stack.push(b);
	}



	void read_0(VMCore & core) { core.stack.push(core.stack.read(0)); }
	void read_1(VMCore & core) { core.stack.push(core.stack.read(1)); }
	void read_2(VMCore & core) { core.stack.push(core.stack.read(2)); }
	void read_3(VMCore & core) { core.stack.push(core.stack.read(3)); }

	void write_0(VMCore & core) { core.stack.write(0, core.stack.pop()); }
	void write_1(VMCore & core) { core.stack.write(1, core.stack.pop()); }
	void write_2(VMCore & core) { core.stack.write(2, core.stack.pop()); }
	void write_3(VMCore & core) { core.stack.write(3, core.stack.pop()); }
}