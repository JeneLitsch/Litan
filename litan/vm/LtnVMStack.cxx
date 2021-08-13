#include "LtnVM.hxx"

void ltn::vm::VM::stackPush(){
	const std::uint64_t value = env.acc.popU();
	const std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	stack.push(value);
}

void ltn::vm::VM::stackPop(){
	const std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	const std::uint64_t value = stack.top();
	stack.pop();
	env.acc.push(value);
}

void ltn::vm::VM::stackTop(){
	const std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	const std::uint64_t value = stack.top();
	env.acc.push(value);
}

void ltn::vm::VM::stackEmpty(){
	const std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	env.acc.push(std::uint64_t(stack.empty()));
}

void ltn::vm::VM::stackSize(){
	const std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	env.acc.push(std::uint64_t(stack.size()));
}

void ltn::vm::VM::stackClear(){
	const std::uint64_t ptr = env.acc.popU();
	auto & stack = env.heap.access<HeapStack>(ptr);
	stack = {};
}

