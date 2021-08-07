#include "LtnVM.hxx"
#include <cmath>

// Math Instruction
void ltn::VM::addf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(l + r);
}

void ltn::VM::subf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(l - r);
}

void ltn::VM::mltf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	
	this->env.acc.push(l * r);
}

void ltn::VM::divf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	
	this->env.acc.push(l / r);
}

void ltn::VM::powf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	
	this->env.acc.push(std::pow(l,r));
}

void ltn::VM::modf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(std::fmod(l,r));
}

void ltn::VM::mnsf(){
	this->env.acc.push(-this->env.acc.popF());
}

void ltn::VM::minf(){
	const double a = this->env.acc.popF();
	const double b = this->env.acc.popF();
	this->env.acc.push(std::min(a, b));
}

void ltn::VM::maxf(){
	const double a = this->env.acc.popF();
	const double b = this->env.acc.popF();
	this->env.acc.push(std::max(a, b));
}


// Comparison
void ltn::VM::eqlf(){
	const std::uint8_t invert = this->getArg8();
	const double l = this->env.acc.popF();
	const double r = this->env.acc.popF();
	const bool result = (l == r) != (invert & 0x01);
	this->env.acc.push(result);
}
void ltn::VM::smlf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(l < r);
}
void ltn::VM::bgrf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(l > r);
}
void ltn::VM::spshf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	if(l == r) return this->env.acc.push(0L);
	if(l > r) return this->env.acc.push(1L);
	if(l < r) return this->env.acc.push(-1L);
}