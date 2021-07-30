#include "LtnVM.hxx"

// bitwise
void ltn::VM::bit_or(){
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l | r);
}
void ltn::VM::bit_and(){
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l & r);
}
void ltn::VM::bit_xor(){
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l ^ r);
}