#include "LtnVM.hxx"
#include "LtnPopFromEmpty.hxx"

// deque instructions
void ltn::VM::dequeNew(){
	this->env.acc.push(this->env.heap.allocate(HeapObject::Type::DEQUE));
}


void ltn::VM::dequeClear(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.access<HeapDeque>(ptr).clear();
}

void ltn::VM::dequeSize(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapDeque>(ptr).size());
}


void ltn::VM::dequeEmpty(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapDeque>(ptr).empty());
}


void ltn::VM::dequePushF(){
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	deque.insert(deque.begin(), value);
}

void ltn::VM::dequePushB(){
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	deque.push_back(value);
}

void ltn::VM::dequePopF(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	if(deque.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(deque.front());
	deque.erase(deque.begin());
}

void ltn::VM::dequePopB(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	if(deque.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(deque.back());
	deque.pop_back();
}

void ltn::VM::dequeFront(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	this->env.acc.push(deque.front());
}

void ltn::VM::dequeBack(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & deque = this->env.heap.access<HeapDeque>(ptr);
	this->env.acc.push(deque.back());
}
