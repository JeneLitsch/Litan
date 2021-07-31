#include "LtnVM.hxx"

// Heap instructions
void ltn::VM::heapAllocate(){
	const HeapType type = static_cast<HeapType>(getArg8());
	this->env.acc.push(this->env.heap.allocate(type));
}

// Heap instructions
void ltn::VM::heapDelete(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.destroy(ptr);
}

void ltn::VM::heapExist() {
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.exists(ptr));
}

void ltn::VM::heapIsType() {
	const std::uint64_t ptr = this->env.acc.popU();
	const HeapType typeInst = static_cast<HeapType>(getArg8());
	const HeapType typeHeap = env.heap.access(ptr).type;
	this->env.acc.push(typeInst == typeHeap);
}

void ltn::VM::heapCopy() {
	const std::uint64_t ptr = this->env.acc.popU();
	const std::uint64_t newptr = this->env.heap.copy(ptr);
	this->env.acc.push(newptr);
}
