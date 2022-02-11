#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>
#include <sstream>

namespace ltn::vm {
	namespace {
		std::uint64_t unwind(Stack & stack) {
			while(stack.depth()) {
				const auto handler = stack.getExceptHandler();
				if(handler != 0) {
					stack.setExceptHandler(0);
					return handler;
				}
				stack.popFrame();
			}
			throw std::runtime_error{"Unhandled Exception"};
		}
	}

	void LtnVM::tRy() {
		const auto addr = this->fetchUint();
		this->stack.setExceptHandler(addr);
	}

	void LtnVM::thr0w() {
		this->pc = unwind(this->stack);
	}


	void LtnVM::state() {
		const auto regSize = this->reg.size();
		const auto stackSize = this->stack.size();
		const auto heapSize = this->heap.size();
		std::stringstream ss;
		ss << "register size: " << regSize << "\n";
		ss << "stack size: " << stackSize << "\n";
		ss << "heap size: " << heapSize << "\n";
		const auto refToString = this->heap.alloc<String>({ss.str()});
		this->reg.push(Value{refToString, Value::Type::STRING});
	}
}