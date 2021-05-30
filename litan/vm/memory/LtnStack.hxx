#pragma once
#include <stack>
#include "LtnStackFrame.hxx"
namespace ltn {
	class Stack {
	public:
		inline void push(std::uint64_t jumpback) {
			this->callStack.push(StackFrame(jumpback));
		}
		inline void pop() {
			this->callStack.pop();
		}
		inline StackFrame & get() {
			return this->callStack.top();
		}
		inline void clear() {
			this->callStack = {};
		}
	private:
		std::stack<StackFrame> callStack;

	};
}
