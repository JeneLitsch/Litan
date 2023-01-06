#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/index.hxx"

namespace ltn::vm::inst {
	void scrap(VmCore & core) {
		core.reg.pop();
	}



	void duplicate(VmCore & core) {
		core.reg.push(core.reg.peek());
	}



	void makevar(VmCore & core) {
		core.stack.make_var();
	}



	void read_x(VmCore & core) {
		const auto addr = core.fetch_uint();
		const auto value = core.stack.read(addr);
		core.reg.push(value);
	}



	void write_x(VmCore & core) {
		const auto addr = core.fetch_uint();
		const auto value = core.reg.pop();
		core.stack.write(addr, value);
	}



	void swap(VmCore & core) {
		const auto a = core.reg.pop();
		const auto b = core.reg.pop();
		core.reg.push(a);
		core.reg.push(b);
	}



	void read_0(VmCore & core) { core.reg.push(core.stack.read(0)); }
	void read_1(VmCore & core) { core.reg.push(core.stack.read(1)); }
	void read_2(VmCore & core) { core.reg.push(core.stack.read(2)); }
	void read_3(VmCore & core) { core.reg.push(core.stack.read(3)); }

	void write_0(VmCore & core) { core.stack.write(0, core.reg.pop()); }
	void write_1(VmCore & core) { core.stack.write(1, core.reg.pop()); }
	void write_2(VmCore & core) { core.stack.write(2, core.reg.pop()); }
	void write_3(VmCore & core) { core.stack.write(3, core.reg.pop()); }
}