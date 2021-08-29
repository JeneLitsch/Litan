#include "LtnVM.hxx"

// Heap instructions
void ltn::vm::VM::heapAllocate(){
	const HeapType type = static_cast<HeapType>(getArg8());
	if(type == HeapType::STRUCT) {
		const std::uint32_t size = this->getArg32();
		this->env.acc.push(this->env.heap.allocate(size));
	}
	else {
		this->env.acc.push(this->env.heap.allocate(type));
	}
}

// Heap instructions
void ltn::vm::VM::heapDelete(){
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.destroy(ptr);
}

void ltn::vm::VM::heapExist() {
	const std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.exists(ptr));
}

void ltn::vm::VM::heapIsType() {
	const std::uint64_t ptr = this->env.acc.popU();
	const HeapType typeInst = static_cast<HeapType>(getArg8());
	const HeapType typeHeap = env.heap.access(ptr).type;
	this->env.acc.push(typeInst == typeHeap);
}

void ltn::vm::VM::heapCopy() {
	const std::uint64_t ptr = this->env.acc.popU();
	const std::uint64_t newptr = this->env.heap.copy(ptr);
	this->env.acc.push(newptr);
}
