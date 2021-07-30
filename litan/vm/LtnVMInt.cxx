#include "LtnVM.hxx"
#include <cmath>

// Math Instruction
void ltn::VM::addi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l + r);
}

void ltn::VM::subi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l - r);
}

void ltn::VM::mlti(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l * r);
}

void ltn::VM::divi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l / r);
}

void ltn::VM::powi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(static_cast<std::int64_t>(std::pow(l, r)));
}

void ltn::VM::modi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l % r);
}

void ltn::VM::inci(){
	this->env.acc.top()++;
}

void ltn::VM::deci(){
	this->env.acc.top()--;
}

void ltn::VM::mnsi(){
	this->env.acc.push(-this->env.acc.popI());
}

void ltn::VM::mini(){
	const std::int64_t a = this->env.acc.popI();
	const std::int64_t b = this->env.acc.popI();
	this->env.acc.push(std::min(a, b));
}

void ltn::VM::maxi(){
	const std::int64_t a = this->env.acc.popI();
	const std::int64_t b = this->env.acc.popI();
	this->env.acc.push(std::max(a, b));
}



// Comparison
void ltn::VM::eqli(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l == r);
}

void ltn::VM::smli(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l < r);
}

void ltn::VM::bgri(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l > r);
}

void ltn::VM::spshi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	if(l == r) return this->env.acc.push(0L);
	if(l > r) return this->env.acc.push(1L);
	if(l < r) return this->env.acc.push(-1L);
}