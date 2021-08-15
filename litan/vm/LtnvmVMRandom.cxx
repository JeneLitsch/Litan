#include "LtnVM.hxx"
void ltn::vm::VM::randInt() {
	const std::int64_t a = this->env.acc.popI();
	const std::int64_t b = this->env.acc.popI();
	const std::int64_t r = std::uniform_int_distribution(std::min(a, b), std::max(a, b))(this->random);
	this->env.acc.push(r);
}

void ltn::vm::VM::randFloat() {
	const double a = this->env.acc.popF();
	const double b = this->env.acc.popF();
	const double r = std::uniform_real_distribution(std::min(a, b), std::max(a, b))(this->random);
	this->env.acc.push(r);
}

void ltn::vm::VM::randNorm() {
	const double r = std::uniform_real_distribution(0.0, 1.0)(this->random);
	this->env.acc.push(r);
}

void ltn::vm::VM::randUnit() {
	const double r = std::uniform_real_distribution(-1.0, 1.0)(this->random);
	this->env.acc.push(r);
}