#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <iostream>
#include <sstream>
#include "ltnvm/convert.hxx"
#include "ltnvm/cast.hxx"

namespace ltn::vm::inst {
	namespace {
		const std::uint8_t * unwind(Stack & stack) {
			while(stack.depth()) {
				const auto handler = stack.get_except_handler();
				if(handler != 0) {
					return handler;
				}
				stack.pop_frame();
			}
			return nullptr;
		}
	}



	void tRy(VmCore & core) {
		const auto address = core.fetch_uint();
		core.stack.set_except_handler(core.code_begin + address);
	}



	void thr0w(VmCore & core) {
		const auto except = core.stack.pop();
		if(auto address = unwind(core.stack)) {
			core.pc = address;
			const auto jumpback = core.stack.pop_frame();
			// These 2 were in the wrong order
			core.stack.push(except);
			core.stack.push_frame(jumpback, 1);		
		}
		else {
			throw Unhandled {
				.exception = Exception{
					.msg = cast::to_string(except, core.heap)
				}
			};
		}
	}
}