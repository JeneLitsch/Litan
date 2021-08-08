#include "LtnVM.hxx"
#include <iostream>

// copy value from memory to acc
void ltn::VM::load(){
	const std::uint8_t immediate = this->getArg8();
	const std::uint64_t addr = immediate ? this->getArg32() : this->env.acc.popU();
	this->env.acc.push(this->env.stack.read(addr));
}

// pop value from acc and write to memory
void ltn::VM::store(){
	const std::uint8_t immediate = this->getArg8();
	const std::uint64_t addr = immediate ? this->getArg32() : this->env.acc.popU();
	this->env.stack.write(addr, this->env.acc.popU());
}

void ltn::VM::copy(){
	this->env.acc.push(this->env.acc.top());
}

void ltn::VM::size(){
	this->env.acc.push(this->env.acc.size());
}


// pop and discard one value from acc
void ltn::VM::scrap(){
	this->env.acc.popU();
}

// discard entire accStack
void ltn::VM::clear(){
	this->env.acc.reset();
}

void ltn::VM::stackalloc() {
	this->env.stack.allocate(this->getArg32());
}