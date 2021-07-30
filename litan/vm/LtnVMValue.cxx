#include "LtnVM.hxx"
#include <cmath>

void ltn::VM::casti(){
	switch (this->getArg8()) {
	case 1:
		return this->env.acc.push(static_cast<std::int64_t>(std::round(this->env.acc.popF())));
	case 2:
		return this->env.acc.push(static_cast<std::int64_t>(std::floor(this->env.acc.popF())));
	case 3:
		return this->env.acc.push(static_cast<std::int64_t>(std::ceil(this->env.acc.popF())));
	default:
		return this->env.acc.push(static_cast<std::int64_t>(this->env.acc.popF()));
	}
}

void ltn::VM::castf(){
	this->env.acc.push(static_cast<double>(this->env.acc.popI()));
}

// new inst (can be merged with bitxor)
// load a value in the lower 32 bits
void ltn::VM::newl(){
	this->env.acc.push(static_cast<std::uint64_t>(this->getArg32()));
}

// load a value in the upper 32 bits
void ltn::VM::newu(){
	this->env.acc.push(static_cast<std::uint64_t>(this->getArg32()) << 32);
}

