#include "LtnVM.hxx"
#include "LtnvmIndexAccessViolation.hxx"

void ltn::vm::VM::structRead(){
	const std::uint64_t idx = this->getArg32();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & strukt = this->env.heap.access<HeapStruct>(ptr);
	if(idx < strukt.members.size()){
		this->env.acc.push(strukt.members[idx]);
	}
	else{
		throw IndexAccessViolation(ptr, idx, "Struct");
	}
}

void ltn::vm::VM::structWrite(){
	const std::uint64_t value = this->env.acc.popU();
	const std::uint64_t idx = this->getArg32();
	const std::uint64_t ptr = this->env.acc.popU();
	auto & strukt = this->env.heap.access<HeapStruct>(ptr);
	if(idx < strukt.members.size()){
		strukt.members[idx] = value;
	}
	else{
		throw IndexAccessViolation(ptr, idx, "Struct");
	}
}