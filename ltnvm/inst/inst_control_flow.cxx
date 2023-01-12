#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/convert.hxx"
#include <sstream>
#include <stack>



namespace ltn::vm::inst {
	void jump(VmCore & core) {
		const auto addr = core.fetch_uint(); 
		core.pc = addr;
	}



	void call(VmCore & core) {
		const auto addr = core.fetch_uint(); 
		const auto arity = core.fetch_byte();
		core.stack.push_frame(core.pc, arity);
		core.pc = addr;
	}



	void reTurn(VmCore & core) {
		auto return_value = core.stack.pop();
		core.pc = core.stack.pop_frame();
		core.stack.push(return_value);
	}



	void iF(VmCore & core) {
		const auto value = core.stack.pop();
		const auto elseAddr = core.fetch_uint();
		if(!convert::to_bool(value)) {
			core.pc = elseAddr;
		}
	}



	void parameters(VmCore & core) {
		const auto count = core.fetch_byte();
		// auto [begin, end] = core.stack.peek(count);
		// for(auto it = begin; it != end; it++) {
		// 	core.stack.make_var(*it);
		// }
		// core.stack.remove(count);
	}



	void error(VmCore &) {
		throw value::null;
	}



	void exit(VmCore & core) {
		throw core.stack.pop();
	}
}