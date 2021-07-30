#include "LtnVM.hxx"

// Heap instructions
void ltn::VM::heapDel(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.destroy(ptr);
}

void ltn::VM::heapExist() {
	std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.exists(ptr));
}

void ltn::VM::heapCopy() {
	std::uint64_t ptr = this->env.acc.popU();
	std::uint64_t newptr = this->env.heap.copy(ptr);
	this->env.acc.push(newptr);
}
