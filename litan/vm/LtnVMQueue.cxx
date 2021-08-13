#include "LtnVM.hxx"

void ltn::vm::VM::queuePush(){
	const std::uint64_t value = env.acc.popU();
	const std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	queue.push(value);
}

void ltn::vm::VM::queuePop(){
	const std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	const std::uint64_t value = queue.front();
	queue.pop();
	env.acc.push(value);
}

void ltn::vm::VM::queueFront(){
	const std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	const std::uint64_t value = queue.front();
	env.acc.push(value);
}

void ltn::vm::VM::queueEmpty(){
	const std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	env.acc.push(std::uint64_t(queue.empty()));
}

void ltn::vm::VM::queueSize(){
	const std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	env.acc.push(std::uint64_t(queue.size()));
}

void ltn::vm::VM::queueClear(){
	const std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	queue = {};
}

