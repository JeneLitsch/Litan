#pragma once
#include "LtnvmRegister.hxx"
#include "LtnvmHeap.hxx"
#include "LtnvmStack.hxx"
#include "LtnvmLoop.hxx"
namespace ltn::vm {
	struct Environment {
		Register acc;
		Heap heap;
		Stack stack;
		std::stack<Loop, std::vector<Loop>> loops;
		
		std::uint64_t * ip;
		struct {
			std::vector<std::uint64_t> instructions;
			std::uint64_t * start;
		} bytecode;

		inline std::uint64_t getPc() {
			return static_cast<std::uint64_t>(std::distance(this->bytecode.start, this->ip));
		}

		inline void jump(std::uint64_t addr) {
			this->ip = this->bytecode.start + addr; 
		}
	};
}