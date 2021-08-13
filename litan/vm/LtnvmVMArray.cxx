#include "LtnVM.hxx"
#include "LtnvmAccessViolation.hxx"
#include "LtnvmIndexAccessViolation.hxx"
#include "LtnvmPointerAccessViolation.hxx"
#include "LtnvmPopFromEmpty.hxx"

// Array instructions
void ltn::vm::VM::arrayClear(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.access<HeapArray>(ptr).clear();
}

void ltn::vm::VM::arrayGet(){
	const std::uint64_t idx = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	if(idx < array.size()){
		this->env.acc.push(array[idx]);
	}
	else{
		throw IndexAccessViolation(ptr, idx, "Array");
	}
}

void ltn::vm::VM::arraySet(){
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t idx = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	if(idx < array.size()){
		array[idx] = value;
	}
	else{
		throw IndexAccessViolation(ptr, idx, "Array");
	}
}


void ltn::vm::VM::arraySize(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapArray>(ptr).size());
}

void ltn::vm::VM::arrayEmpty(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapArray>(ptr).empty());
}

void ltn::vm::VM::arrayFill() {
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	std::vector<std::uint64_t> & array = this->env.heap.access<HeapArray>(ptr);
	std::fill(array.begin(), array.end(), value);
}

void ltn::vm::VM::arrayResize(){
	const std::uint64_t size = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.access<HeapArray>(ptr).resize(size, 0);
}

void ltn::vm::VM::arrayErase(){
	const std::uint64_t idx = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	std::vector<std::uint64_t> & array = this->env.heap.access<HeapArray>(ptr);
	array.erase(array.begin() + long(idx));
}

void ltn::vm::VM::arrayInsert(){
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t idx = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	std::vector<std::uint64_t> & array = this->env.heap.access<HeapArray>(ptr);
	array.insert(array.begin() + long(idx), value);
}

void ltn::vm::VM::arrayPushBack(){
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	array.push_back(value);
}


void ltn::vm::VM::arrayPopBack(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	if(array.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(array.back());
	array.pop_back();
}

void ltn::vm::VM::arrayFront(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	this->env.acc.push(array.front());
}

void ltn::vm::VM::arrayBack(){
	const std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	this->env.acc.push(array.back());
}