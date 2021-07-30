#include "LtnVM.hxx"

// logic
void ltn::VM::log_or(){
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l || r);
}
void ltn::VM::log_and() {
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l && r);
}
void ltn::VM::log_xor() {
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(!l != !r);
}