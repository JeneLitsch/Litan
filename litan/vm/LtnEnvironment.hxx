#pragma once
#include "LtnRegister.hxx"
#include "LtnHeap.hxx"
#include "LtnStack.hxx"
#include "LtnLoop.hxx"
namespace ltn {
	struct Environment {
		Register acc;
		Heap heap;
		Stack stack;
		std::stack<Loop> loops;
		std::vector<std::uint64_t> instructions;
		std::uint64_t pc;
	};
}