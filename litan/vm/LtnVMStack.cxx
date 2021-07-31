#include "LtnVM.hxx"

void ltn::VM::stackPush(){
	std::uint64_t value = env.acc.popU();
	std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	stack.push(value);
}

void ltn::VM::stackPop(){
	std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	std::uint64_t value = stack.top();
	stack.pop();
	env.acc.push(value);
}

void ltn::VM::stackTop(){
	std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	std::uint64_t value = stack.top();
	env.acc.push(value);
}

void ltn::VM::stackEmpty(){
	std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	env.acc.push(std::uint64_t(stack.empty()));
}

void ltn::VM::stackSize(){
	std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	env.acc.push(std::uint64_t(stack.size()));
}

void ltn::VM::stackClear(){
	std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	stack = {};
}

