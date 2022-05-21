#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <iostream>
#include <sstream>
#include "ltnvm/convert.hxx"

namespace ltn::vm::inst {
	namespace {
		void clearTopFrame(Stack & stack) {
			const auto jumpback = stack.pop_frame();
			stack.push_frame(jumpback);
		}


		std::uint64_t unwind(Stack & stack) {
			while(stack.depth()) {
				const auto handler = stack.get_except_handler();
				if(handler != 0) {
					return handler;
				}
				stack.pop_frame();
			}
			throw std::runtime_error{"Unhandled Exception"};
		}
	}

	void tRy(VmCore & core) {
		const auto addr = core.fetch_uint();
		const auto regSize = core.reg.size();
		core.stack.set_except_handler(addr);
		core.stack.set_regsize(regSize);
	}


	void thr0w(VmCore & core) {
		const auto except = core.reg.pop();
		core.pc = unwind(core.stack);
		const auto regSize = core.stack.get_regsize();
		core.reg.resize(regSize);
		clearTopFrame(core.stack);		
		core.reg.push(except);
		
	}


	void state(VmCore & core) {
		const auto regSize = core.reg.size();
		const auto stackSize = core.stack.size();
		const auto heapSize = core.heap.size();
		std::stringstream ss;
		ss << "register size: " << regSize << "\n";
		ss << "stack size: " << stackSize << "\n";
		ss << "heap size: " << heapSize << "\n";
		const auto refToString = core.heap.alloc<String>({ss.str()});
		core.reg.push(Value{refToString, Value::Type::STRING});
	}
}