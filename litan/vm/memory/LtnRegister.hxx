#pragma once
#include <cstdint>
#include <array>
#include "LtnFloat.hxx"
namespace ltn{
	class Register {
	public:
		inline std::uint64_t & top() { return this->stack[this->current-1]; }
		inline std::uint64_t size() const { return this->current; }
		inline std::uint64_t isFull() const { return this->size() >= 256; }

		inline std::int64_t popI() { return static_cast<std::int64_t>(this->pop()); }
		inline std::uint64_t popU() { return this->pop(); }
		inline double popF() { return Float::uintToDouble(this->pop());}

		inline void push(std::int64_t val) { this->push(static_cast<std::uint64_t>(val)); }
		inline void push(bool val) { this->push(static_cast<std::uint64_t>(val)); }
		inline void push(double val) { this->push(Float::doubleToUint(val)); }
		inline void push(std::uint64_t value) {
			this->stack[current] = value;
			this->current++; 
		}

		void reset();

		// const std::stack<std::uint64_t> & getStack() const;
	private:
		inline std::uint64_t pop() {
			std::uint64_t value = this->top();
			this->current--;
			return value;
		}
		std::uint64_t current;
		std::array<std::uint64_t, 256> stack;
	};
}
