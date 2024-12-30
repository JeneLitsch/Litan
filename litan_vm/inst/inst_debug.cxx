#include "instructions.hxx"
#include "litan_vm/utils/type_check.hxx"
#include <iostream>
#include <sstream>
#include "litan_vm/utils/convert.hxx"
#include "litan_vm/utils/cast.hxx"

namespace ltn::vm::inst {
	namespace {
		std::uint64_t unwind(VMStack & stack) {
			while(stack.depth()) {
				const auto handler = stack.get_except_handler();
				if(handler != 0) {
					return handler;
				}
				stack.pop_frame();
			}
			return 0;
		}
	}



	void thr0w(VMCore & core) {
		const auto except = core.stack.pop();
		if(auto address = unwind(core.stack)) {
			core.pc = core.code_begin + address;
			const auto * context = core.stack.get_current_frame().context;
			const auto jumpback = core.stack.pop_frame();
			// These 2 were in the wrong order
			core.stack.push(except);
			core.stack.push_frame(jumpback, 1, context);		
		}
		else {
			throw Unhandled {
				.exception = Exception{
					.msg = cast::to_string(except)
				}
			};
		}
	}
}