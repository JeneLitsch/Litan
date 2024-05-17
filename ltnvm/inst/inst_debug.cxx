#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include <iostream>
#include <sstream>
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/utils/cast.hxx"

namespace ltn::vm::inst {
	namespace {
		const std::uint8_t * unwind(VMStack & stack) {
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



	void tRy(VMCore & core) {
		const auto address = core.fetch_uint();
		core.stack.set_except_handler(core.code_begin + address);
	}



	void thr0w(VMCore & core) {
		const auto except = core.stack.pop();
		if(auto address = unwind(core.stack)) {
			core.pc = address;
			const auto * context = core.stack.get_current_frame().context;
			const auto jumpback = core.stack.pop_frame();
			// These 2 were in the wrong order
			core.stack.push(except);
			core.stack.push_frame(jumpback, 1, context);		
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