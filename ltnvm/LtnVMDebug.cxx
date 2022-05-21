#include "LtnVM.hxx"
#include "type_check.hxx"
#include <iostream>
#include <sstream>
#include "convert.hxx"

namespace ltn::vm {
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

	void LtnVM::tRy() {
		const auto addr = this->fetch_uint();
		const auto regSize = this->core.reg.size();
		this->core.stack.set_except_handler(addr);
		this->core.stack.set_regsize(regSize);
	}


	void LtnVM::thr0w() {
		const auto except = this->core.reg.pop();
		this->core.pc = unwind(this->core.stack);
		const auto regSize = this->core.stack.get_regsize();
		this->core.reg.resize(regSize);
		clearTopFrame(this->core.stack);		
		this->core.reg.push(except);
		
	}


	void LtnVM::state() {
		const auto regSize = this->core.reg.size();
		const auto stackSize = this->core.stack.size();
		const auto heapSize = this->core.heap.size();
		std::stringstream ss;
		ss << "register size: " << regSize << "\n";
		ss << "stack size: " << stackSize << "\n";
		ss << "heap size: " << heapSize << "\n";
		const auto refToString = this->core.heap.alloc<String>({ss.str()});
		this->core.reg.push(Value{refToString, Value::Type::STRING});
	}
}