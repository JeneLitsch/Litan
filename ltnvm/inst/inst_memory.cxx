#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/index.hxx"

namespace ltn::vm::inst {
	void scrap(VmCore & core) {
		core.stack.pop();
	}



	void duplicate(VmCore & core) {
		core.stack.push(core.stack.peek());
	}



	void alloc_local(VmCore & core) {
		const auto amount = core.fetch_byte();
		for(std::uint16_t i = 0; i < amount; ++i) {
			core.stack.push(value::null);
		}
	}



	void read_x(VmCore & core) {
		const auto address = core.fetch_uint();
		const auto value = core.stack.read(address);
		core.stack.push(value);
	}



	void write_x(VmCore & core) {
		const auto address = core.fetch_uint();
		const auto value = core.stack.pop();
		core.stack.write(address, value);
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