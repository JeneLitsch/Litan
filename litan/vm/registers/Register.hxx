#pragma once
#include <cstdint>
#include <array>
namespace ltn{
	class Register {
	public:
		inline void push(std::uint64_t value) {
			this->stack[current] = value;
			this->current++; 
		}
		inline std::uint64_t pop() {
			std::uint64_t value = this->top();
			this->current--;
			return value;
		}
		inline std::uint64_t & top() { return this->stack[this->current-1]; }
		inline std::uint64_t size() const { return this->current; }
		inline std::uint64_t isFull() const { return this->size() >= 256; }

		void reset();

		// const std::stack<std::uint64_t> & getStack() const;
	private:
		std::uint64_t current;
		std::array<std::uint64_t, 256> stack;
	};
}