#include "LtnVM.hxx"
#include <cmath>

// Math Instruction
void ltn::VM::addf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(l + r);
}

void ltn::VM::subf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(l - r);
}

void ltn::VM::mltf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	
	this->env.acc.push(l * r);
}

void ltn::VM::divf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	
	this->env.acc.push(l / r);
}

void ltn::VM::powf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	
	this->env.acc.push(std::pow(l,r));
}

void ltn::VM::modf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
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
	double l = this->env.acc.popF();
	double r = this->env.acc.popF();
	this->env.acc.push(l == r);
}
void ltn::VM::smlf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(l < r);
}
void ltn::VM::bgrf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(l > r);
}
void ltn::VM::spshf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	if(l == r) return this->env.acc.push(0L);
	if(l > r) return this->env.acc.push(1L);
	if(l < r) return this->env.acc.push(-1L);
}