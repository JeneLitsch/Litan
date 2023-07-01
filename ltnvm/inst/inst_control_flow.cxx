#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/convert.hxx"
#include <sstream>
#include <stack>



namespace ltn::vm::inst {
	void jump(VmCore & core) {
		const auto address = core.fetch_uint(); 
		core.pc = core.code_begin + address;
	}



	void call(VmCore & core) {
		const auto address = core.fetch_uint(); 
		const auto arity = core.fetch_byte();
		core.stack.push_frame(core.pc, arity);
		core.pc = core.code_begin + address;
	}



	void reTurn(VmCore & core) {
		auto return_value = core.stack.pop();
		core.pc = core.stack.pop_frame();
		core.stack.push(return_value);
	}



	void iF(VmCore & core) {
		const auto value = core.stack.pop();
		const auto elseAddr = core.fetch_uint();
		if(!convert::to_bool(value, core)) {
			core.pc = core.code_begin + elseAddr;
		}
	}



	void error(VmCore &) {
		throw value::null;
	}



	void exit(VmCore & core) {
		throw core.stack.pop();
	}


	void for_next(VmCore & core) {
		const auto iter = core.stack.peek();
		core.stack.push(iterator::next(iter));
		core.stack.push(!is_iterator_stop(core.stack.peek())); 
		inst::iF(core);
	}
}