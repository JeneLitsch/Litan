#include "LtnVM.hxx"
#include <iostream>

void ltn::vm::VM::stringAdd() {
	const std::uint64_t ptr2 = this->env.acc.popU();	
	const std::uint64_t ptr1 = this->env.acc.popU();
	const std::uint64_t ptr3 = this->env.heap.allocate(HeapType::STRING);
	const HeapString & str1 = this->env.heap.access<HeapString>(ptr1);
	const HeapString & str2 = this->env.heap.access<HeapString>(ptr2);
	HeapString & str3 = this->env.heap.access<HeapString>(ptr3);
	str3 = str1 + str2;
	this->env.acc.push(ptr3);
}

void ltn::vm::VM::stringData() {
	const std::uint64_t ptr = this->env.acc.top();
	const std::uint8_t len = this->getArg8();
	std::string str = "";
	for(unsigned int i = 2; i < 2 + len; i++) {
		const char chr = this->getArg8(i);
		str.push_back(chr);
	}
	this->env.heap.access<HeapString>(ptr) += str;
}
