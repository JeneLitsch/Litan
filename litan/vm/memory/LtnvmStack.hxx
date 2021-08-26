#pragma once
#include <stack>
namespace ltn::vm {
	class Stack {
	public:
		// inits a new stackframe
		/* |                 |
		   | ...             |
		   | jumpback        |
		   | oldStackPointer |
		   |=================|
		   | ...old Frame... |
		*/
		inline void call(const std::uint64_t jumpback) {
			const std::uint64_t oldStackPointer = stackPointer;
			const std::uint64_t newStackPointer = this->callStack.size(); 
			this->callStack.push_back(oldStackPointer);
			this->callStack.push_back(jumpback);
			this->stackPointer = newStackPointer;
		}
		// adds new space on top of the current stackFrame
		inline void allocate(const std::size_t size) {
			this->callStack.resize(this->callStack.size() + size);
		}
		inline std::uint64_t rtrn() {
			const std::uint64_t jumpback = this->callStack[stackPointer + 1];
			const std::uint64_t newStackPointer = this->callStack[stackPointer];
			this->callStack.resize(stackPointer);
			this->stackPointer = newStackPointer;
			return jumpback;
		}
		inline std::uint64_t read(const std::uint64_t addr) {
			return this->callStack[this->stackPointer + 2 + addr];
		}
		inline void write(const std::uint64_t addr, const std::uint64_t value) {
			this->callStack[this->stackPointer + 2 + addr] = value;
		}
		inline void clear() {
			this->callStack = {};
		}
	private:
		std::vector<std::uint64_t> callStack;
		std::size_t stackPointer;
	};
}
