#include "LtnVM.hxx"

// logic
void ltn::VM::log_or(){
	const std::uint64_t r = this->env.acc.popU();
	const std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l || r);
}


void ltn::VM::log_and() {
	const std::uint64_t r = this->env.acc.popU();
	const std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l && r);
}


void ltn::VM::log_xor() {
	const std::uint64_t r = this->env.acc.popU();
	const std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(!l != !r);
}


void ltn::VM::log_not() {
	const std::uint64_t x = this->env.acc.popU();
	this->env.acc.push(!static_cast<bool>(x));
}