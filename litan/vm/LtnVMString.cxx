#include "LtnVM.hxx"
#include <iostream>

void ltn::VM::stringNew() {
	this->env.acc.push(this->env.heap.allocate(HeapObject::Type::STRING));
}

void ltn::VM::stringAdd() {
	std::uint64_t ptr2 = this->env.acc.popU();	
	std::uint64_t ptr1 = this->env.acc.popU();
	std::uint64_t ptr3 = this->env.heap.allocate(HeapObject::Type::STRING);
	HeapString str1 = this->env.heap.access<HeapString>(ptr1);
	HeapString str2 = this->env.heap.access<HeapString>(ptr2);
	HeapString str3 = this->env.heap.access<HeapString>(ptr3);
	str3 = str1 + str2;
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
	this->env.heap.access<HeapString>(ptr) += str;
}

void ltn::VM::stringPrint() {
	std::uint64_t ptr = this->env.acc.popU();
	std::cout << this->env.heap.access<HeapString>(ptr) << std::endl;
}