#include "LtnVM.hxx"
#include <iostream>

// copy value from memory to acc
void ltn::vm::VM::load(){
	const std::uint8_t immediate = this->getArg8();
	const std::uint64_t addr = immediate ? this->getArg32() : this->env.acc.popU();
	this->env.acc.push(this->env.stack.read(addr));
}

// pop value from acc and write to memory
void ltn::vm::VM::store(){
	const std::uint8_t immediate = this->getArg8();
	const std::uint64_t addr = immediate ? this->getArg32() : this->env.acc.popU();
	const std::uint64_t value = this->env.acc.popU();
	this->env.stack.write(addr, value);
}

void ltn::vm::VM::copy(){
	this->env.acc.push(this->env.acc.top());
}

void ltn::vm::VM::size(){
	this->env.acc.push(this->env.acc.size());
}


// pop and discard one value from acc
void ltn::vm::VM::scrap(){
	this->env.acc.popU();
}

void ltn::vm::VM::stackalloc() {
	this->env.stack.allocate(this->getArg32());
}