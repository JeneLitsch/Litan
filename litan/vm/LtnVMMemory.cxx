#include "LtnVM.hxx"
#include <iostream>

// copy value from memory to acc
void ltn::VM::load(){
	std::uint32_t addr = static_cast<std::uint32_t>(this->env.acc.popU());
	this->env.acc.push(this->env.stack.get().memoryBlock[addr]);
}

// pop value from acc and write to memory
void ltn::VM::store(){
	std::uint32_t addr = static_cast<std::uint32_t>(this->env.acc.popU());
	this->env.stack.get().memoryBlock[addr] = this->env.acc.popU();
}

void ltn::VM::copy(){
	this->env.acc.push(this->env.acc.top());
}

void ltn::VM::size(){
	this->env.acc.push(this->env.acc.size());
}

// print or put value into ouput
void ltn::VM::print(){
	switch (this->getArg8()){
	case 0:
		std::cout << this->env.acc.popI() << std::endl;
		break;
	case 1:
		std::cout << this->env.acc.popF() << std::endl;
		break;
	default:
		std::cout << this->env.acc.popU()  << std::endl;
		break;
	}
	
}

// pop and discard one value from acc
void ltn::VM::scrap(){
	this->env.acc.popU();
}

// discard entire accStack
void ltn::VM::clear(){
	this->env.acc.reset();
}

void ltn::VM::init() {
	this->env.stack.push(0); 
}

void ltn::VM::stackalloc() {
	this->env.stack.get().memoryBlock.resize(this->env.stack.get().memoryBlock.size() + this->getArg32());
}