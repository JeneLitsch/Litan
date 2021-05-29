#pragma once
#include "Register.hxx"
#include "LtnFloat.hxx"
#include "LtnStackFrame.hxx"
#include <vector>
#include <stack>
namespace ltn{
	class Environment {
	public:
		// stack register
		Register acc;

		// ram and rom
		std::stack<StackFrame> callStack;
		std::vector<std::uint64_t> instructions;

		// pop value from accStack and convert
		// NOT A INSTRUCTION
		inline std::int64_t pollI() { return static_cast<std::int64_t>(this->acc.pop()); }
		inline std::uint64_t pollU() { return this->acc.pop(); }
		inline double pollF() { return Float::uintToDouble(this->acc.pop());}

		inline void push(std::int64_t val) { this->acc.push(static_cast<std::uint64_t>(val)); }
		inline void push(std::uint64_t val) { this->acc.push(static_cast<std::uint64_t>(val)); }
		inline void push(bool val) { this->acc.push(static_cast<std::uint64_t>(val)); }
		inline void push(double val) { this->acc.push(Float::doubleToUint(val)); }

		inline std::uint64_t resolveAddr(std::uint64_t addr) const { return addr; }

		// status and settings
		std::uint64_t pc;
		bool running;
	};
}