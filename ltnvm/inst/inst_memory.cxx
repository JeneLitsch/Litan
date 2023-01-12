#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/index.hxx"

namespace ltn::vm::inst {
	void scrap(VmCore & core) {
		core.stack.pop();
	}



	void duplicate(VmCore & core) {
		core.stack.push(core.stack.peek());
	}



	void makevar(VmCore & core) {
		core.stack.make_var();
	}



	void read_x(VmCore & core) {
		const auto addr = core.fetch_uint();
		const auto value = core.stack.read(addr);
		core.stack.push(value);
	}



	void write_x(VmCore & core) {
		const auto addr = core.fetch_uint();
		const auto value = core.stack.pop();
		core.stack.write(addr, value);
	}



	void swap(VmCore & core) {
		const auto a = core.stack.pop();
		const auto b = core.stack.pop();
		core.stack.push(a);
		core.stack.push(b);
	}



	void read_0(VmCore & core) { core.stack.push(core.stack.read(0)); }
	void read_1(VmCore & core) { core.stack.push(core.stack.read(1)); }
	void read_2(VmCore & core) { core.stack.push(core.stack.read(2)); }
	void read_3(VmCore & core) { core.stack.push(core.stack.read(3)); }

	void write_0(VmCore & core) { core.stack.write(0, core.stack.pop()); }
	void write_1(VmCore & core) { core.stack.write(1, core.stack.pop()); }
	void write_2(VmCore & core) { core.stack.write(2, core.stack.pop()); }
	void write_3(VmCore & core) { core.stack.write(3, core.stack.pop()); }
}