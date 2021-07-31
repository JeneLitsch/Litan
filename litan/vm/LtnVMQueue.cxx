#include "LtnVM.hxx"

void ltn::VM::queuePush(){
	std::uint64_t value = env.acc.popU();
	std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	queue.push(value);
}

void ltn::VM::queuePop(){
	std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	std::uint64_t value = queue.front();
	queue.pop();
	env.acc.push(value);
}

void ltn::VM::queueFront(){
	std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	std::uint64_t value = queue.front();
	env.acc.push(value);
}

void ltn::VM::queueEmpty(){
	std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	env.acc.push(std::uint64_t(queue.empty()));
}

void ltn::VM::queueSize(){
	std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	env.acc.push(std::uint64_t(queue.size()));
}

void ltn::VM::queueClear(){
	std::uint64_t ptr = env.acc.popU();
	auto & queue = env.heap.access<HeapQueue>(ptr);
	queue = {};
}

