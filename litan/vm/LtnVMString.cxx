#include "LtnVM.hxx"
#include <iostream>

void ltn::VM::stringNew() {
	this->env.acc.push(this->env.heap.allocateString());
}

void ltn::VM::stringAdd() {
	std::uint64_t ptr2 = this->env.acc.popU();	
	std::uint64_t ptr1 = this->env.acc.popU();
	std::uint64_t ptr3 = this->env.heap.allocateString();
	this->env.heap.accessString(ptr3) = this->env.heap.accessString(ptr1) + this->env.heap.accessString(ptr2);
	this->env.acc.push(ptr3);
}

void ltn::VM::stringData() {
	std::uint64_t ptr = this->env.acc.top();
	std::uint8_t len = this->getArg8();
	std::string str = "";
	for(unsigned int i = 2; i < 2 + len; i++) {
		char chr = static_cast<char>((this->currentInstruction >> i*8) & 0xff);
		str.push_back(chr);
	}
	this->env.heap.accessString(ptr) += str;
}

void ltn::VM::stringPrint() {
	std::uint64_t ptr = this->env.acc.popU();
	std::cout << this->env.heap.accessString(ptr) << std::endl;
}