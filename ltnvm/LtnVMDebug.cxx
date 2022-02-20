#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>
#include <sstream>
#include "cast.hxx"

namespace ltn::vm {
	namespace {
		void clearTopFrame(Stack & stack) {
			const auto jumpback = stack.popFrame();
			stack.pushFrame(jumpback);
		}


		std::uint64_t unwind(Stack & stack) {
			while(stack.depth()) {
				const auto handler = stack.getExceptHandler();
				if(handler != 0) {
					return handler;
				}
				stack.popFrame();
			}
			throw std::runtime_error{"Unhandled Exception"};
		}
	}

	void LtnVM::tRy() {
		const auto addr = this->fetchUint();
		const auto regSize = this->reg.size();
		this->stack.setExceptHandler(addr);
		this->stack.setRegSize(regSize);
	}


	void LtnVM::thr0w() {
		const auto except = this->reg.pop();
		this->pc = unwind(this->stack);
		const auto regSize = this->stack.getRegSize();
		this->reg.resize(regSize);
		clearTopFrame(stack);		
		this->reg.push(except);
		
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