#pragma once
#include <stack>
#include "LtnStackFrame.hxx"
namespace ltn {
	class Stack {
	public:
		inline void call(std::uint64_t jumpback) {
			const std::uint64_t oldStackPointer = stackPointer;
			const std::uint64_t newStackPointer = this->callStack.size(); 
			this->callStack.push_back(oldStackPointer);
			this->callStack.push_back(jumpback);
			this->stackPointer = newStackPointer;
		}
		inline void allocate(std::size_t size) {
			this->callStack.resize(this->callStack.size() + size);
		}
		inline void pop() {
			const std::uint64_t newStackPointer = this->callStack[stackPointer];
			this->callStack.resize(stackPointer);
			this->stackPointer = newStackPointer;
		}
		inline std::uint64_t read(std::uint64_t addr) {
			return this->callStack[stackPointer + addr + 2];
		}
		inline void write(std::uint64_t addr, std::uint64_t value) {
			this->callStack[stackPointer + addr + 2] = value;
		}
		inline void clear() {
			this->callStack = {};
		}
		inline std::uint64_t jumpback() {
			return this->callStack[stackPointer + 1];
		}
	private:
		std::vector<std::uint64_t> callStack;
		std::size_t stackPointer;
	};
}
