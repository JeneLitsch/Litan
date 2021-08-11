#include "LtnVM.hxx"
#include "LtnPopFromEmpty.hxx"

// deque instructions
void ltn::VM::dequeClear(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.access<HeapDeque>(ptr).clear();
}

void ltn::VM::dequeSize(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapDeque>(ptr).size());
}


void ltn::VM::dequeEmpty(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapDeque>(ptr).empty());
}


void ltn::VM::dequePushF(){
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	deque.push_front(value);
}

void ltn::VM::dequePushB(){
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	deque.push_back(value);
}

void ltn::VM::dequePopF(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	if(deque.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(deque.front());
	deque.erase(deque.begin());
}

void ltn::VM::dequePopB(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	if(deque.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(deque.back());
	deque.pop_back();
}

void ltn::VM::dequeFront(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	this->env.acc.push(deque.front());
}

void ltn::VM::dequeBack(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	this->env.acc.push(deque.back());
}
