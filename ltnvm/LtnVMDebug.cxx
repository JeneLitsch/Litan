#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>
#include <sstream>

namespace ltn::vm {
	namespace {
		void clearTopFrame(Stack & stack) {
			const auto jb = stack.popFrame();
			stack.pushFrame(jb);
		}

		std::uint64_t unwind(Stack & stack) {
			while(stack.depth()) {
				const auto handler = stack.getExceptHandler();
				if(handler != 0) {
					clearTopFrame(stack);
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
		const auto except = this->reg.pop();
		this->pc = unwind(this->stack);
		this->stack.setException(except);
	}


	void LtnVM::c4tch() {
		const auto except = this->stack.getException();
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