#include "instructions.hxx"
#include "type_check.hxx"
#include "convert.hxx"
#include <sstream>
#include <stack>



namespace ltn::vm::inst {
	void jump(VmCore & core) {
		const auto addr = core.fetch_uint(); 
		core.pc = addr;
	}



	void call(VmCore & core) {
		const auto addr = core.fetch_uint(); 
		core.stack.push_frame(core.pc);
		core.pc = addr;
	}



	void reTurn(VmCore & core) {
		core.pc = core.stack.pop_frame();
	}



	void iF(VmCore & core) {
		const auto value = core.reg.pop();
		const auto elseAddr = core.fetch_uint();
		if(!convert::to_bool(value)) {
			core.pc = elseAddr;
		}
	}



	void parameters(VmCore & core) {
		const auto count = core.fetch_byte();
		auto [begin, end] = core.reg.peek(count);
		for(auto it = begin; it != end; it++) {
			core.stack.make_var(*it);
		}
		core.reg.remove(count);
	}


	void error(VmCore & core) {
		throw value::null;
	}

	void exit(VmCore & core) {
		throw core.reg.pop();
	}
}