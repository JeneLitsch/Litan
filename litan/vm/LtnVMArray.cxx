#include "LtnVM.hxx"
#include "LtnAccessViolation.hxx"
#include "LtnIndexAccessViolation.hxx"
#include "LtnPointerAccessViolation.hxx"
#include "LtnPopFromEmpty.hxx"

// Array instructions
void ltn::VM::arrayNew(){
	this->env.acc.push(this->env.heap.allocate(HeapObject::Type::ARRAY));
}


void ltn::VM::arrayClr(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.access<HeapArray>(ptr).clear();
}

void ltn::VM::arrayGet(){
	std::uint64_t idx = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	if(idx < array.size()){
		this->env.acc.push(array[idx]);
	}
	else{
		throw IndexAccessViolation(ptr, idx, "Array");
	}
}

void ltn::VM::arraySet(){
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t idx = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	if(idx < array.size()){
		array[idx] = value;
	}
	else{
		throw IndexAccessViolation(ptr, idx, "Array");
	}
}


void ltn::VM::arrayLen(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.access<HeapArray>(ptr).size());
}


void ltn::VM::arrayFll() {
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	std::vector<std::uint64_t> & array = this->env.heap.access<HeapArray>(ptr);
	std::fill(array.begin(), array.end(), value);
}

void ltn::VM::arrayRsz(){
	std::uint64_t size = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.access<HeapArray>(ptr).resize(size, 0);
}

void ltn::VM::arrayErs(){
	std::uint64_t idx = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	std::vector<std::uint64_t> & array = this->env.heap.access<HeapArray>(ptr);
	array.erase(array.begin() + long(idx));
}

void ltn::VM::arrayIns(){
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t idx = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	std::vector<std::uint64_t> & array = this->env.heap.access<HeapArray>(ptr);
	array.insert(array.begin() + long(idx), value);
}

void ltn::VM::arrayPushF(){
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	array.insert(array.begin(), value);
}

void ltn::VM::arrayPushB(){
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	array.push_back(value);
}

void ltn::VM::arrayPopF(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	if(array.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(array.front());
	array.erase(array.begin());
}

void ltn::VM::arrayPopB(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	if(array.empty()) {
		throw PopFromEmpty(ptr);
	}
	this->env.acc.push(array.back());
	array.pop_back();
}

void ltn::VM::arrayGetF(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	this->env.acc.push(array.front());
}

void ltn::VM::arrayGetB(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.access<HeapArray>(ptr);
	this->env.acc.push(array.back());
}