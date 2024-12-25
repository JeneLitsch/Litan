#include "instructions.hxx"
#include "litan_vm/utils/type_check.hxx"
#include "litan_vm/utils/index.hxx"

namespace ltn::vm::inst {
	void scrap(VMCore & core) {
		core.stack.pop();
	}



	void duplicate(VMCore & core) {
		core.stack.push(core.stack.peek());
	}



	void load_x(VMCore & core) {
		const auto address = core.fetch_uint();
		const auto value = core.stack.read(address);
		core.stack.push(value);
	}



	void store_x(VMCore & core) {
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



	void load_0(VMCore & core) { core.stack.push(core.stack.read(0)); }
	void load_1(VMCore & core) { core.stack.push(core.stack.read(1)); }
	void load_2(VMCore & core) { core.stack.push(core.stack.read(2)); }
	void load_3(VMCore & core) { core.stack.push(core.stack.read(3)); }

	void store_0(VMCore & core) { core.stack.write(0, core.stack.pop()); }
	void store_1(VMCore & core) { core.stack.write(1, core.stack.pop()); }
	void store_2(VMCore & core) { core.stack.write(2, core.stack.pop()); }
	void store_3(VMCore & core) { core.stack.write(3, core.stack.pop()); }
}