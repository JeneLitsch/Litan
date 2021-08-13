#include "LtnVM.hxx"
#include <cmath>

// Math Instruction
void ltn::vm::VM::addf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(l + r);
}

void ltn::vm::VM::subf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(l - r);
}

void ltn::vm::VM::mltf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	
	this->env.acc.push(l * r);
}

void ltn::vm::VM::divf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	
	this->env.acc.push(l / r);
}

void ltn::vm::VM::powf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	
	this->env.acc.push(std::pow(l,r));
}

void ltn::vm::VM::modf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(std::fmod(l,r));
}

void ltn::vm::VM::mnsf(){
	this->env.acc.push(-this->env.acc.popF());
}

void ltn::vm::VM::minf(){
	const double a = this->env.acc.popF();
	const double b = this->env.acc.popF();
	this->env.acc.push(std::min(a, b));
}

void ltn::vm::VM::maxf(){
	const double a = this->env.acc.popF();
	const double b = this->env.acc.popF();
	this->env.acc.push(std::max(a, b));
}


// Comparison
void ltn::vm::VM::eqlf(){
	const std::uint8_t invert = this->getArg8();
	const double l = this->env.acc.popF();
	const double r = this->env.acc.popF();
	const bool result = (l == r) != (invert & 0x01);
	this->env.acc.push(result);
}
void ltn::vm::VM::smlf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(l < r);
}
void ltn::vm::VM::bgrf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	this->env.acc.push(l > r);
}
void ltn::vm::VM::spshf(){
	const double r = this->env.acc.popF();
	const double l = this->env.acc.popF();
	if(l == r) return this->env.acc.push(0L);
	if(l > r) return this->env.acc.push(1L);
	if(l < r) return this->env.acc.push(-1L);
}