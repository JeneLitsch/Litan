#include "LtnVM.hxx"
#include "LtnPopFromEmpty.hxx"

// deque instructions
void ltn::vm::VM::dequeClear(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.access<HeapDeque>(ptr).clear();
}

void ltn::vm::VM::dequeSize(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapDeque>(ptr).size());
}


void ltn::vm::VM::dequeEmpty(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapDeque>(ptr).empty());
}


void ltn::vm::VM::dequePushF(){
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	deque.push_front(value);
}

void ltn::vm::VM::dequePushB(){
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	deque.push_back(value);
}

void ltn::vm::VM::dequePopF(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	if(deque.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(deque.front());
	deque.erase(deque.begin());
}

void ltn::vm::VM::dequePopB(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	if(deque.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(deque.back());
	deque.pop_back();
}

void ltn::vm::VM::dequeFront(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	this->env.acc.push(deque.front());
}

void ltn::vm::VM::dequeBack(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	this->env.acc.push(deque.back());
}
