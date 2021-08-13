#include "LtnVM.hxx"

// bitwise
void ltn::vm::VM::bit_or(){
	const std::uint64_t r = this->env.acc.popU();
	const std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l | r);
}
void ltn::vm::VM::bit_and(){
	const std::uint64_t r = this->env.acc.popU();
	const std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l & r);
}
void ltn::vm::VM::bit_xor(){
	const std::uint64_t r = this->env.acc.popU();
	const std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l ^ r);
}

void ltn::vm::VM::bit_not() {
	const std::uint64_t x = this->env.acc.popU();
	this->env.acc.push(~x);
}