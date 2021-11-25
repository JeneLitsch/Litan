#include "LtnVM.hxx"
#include "TypeCheck.hxx"



namespace ltn::vm {
	#define FETCH const auto x = this->reg.pop();

	void LtnVM::neg() {
		FETCH
		if(isInt(x)) {
			return this->reg.push({- x.i});
		}
		if(isFloat(x)) {
			return this->reg.push({- x.f});
		}
		throw std::runtime_error{"Cannot negate"};
	}
	void LtnVM::n0t() {
		FETCH
		if(isBool(x)) {
			return this->reg.push({!x.b});
		}
		if(isInt(x)) {
			return this->reg.push({!x.i});
		}
		if(isFloat(x)) {
			return this->reg.push({!x.f});
		}
		throw std::runtime_error{"Cannot apply not"};
	}

	void LtnVM::inc() {
		FETCH
		if(isInt(x)) {
			return this->reg.push({x.i + 1});
		}
		if(isFloat(x)) {
			return this->reg.push({x.f + 1});
		}
		throw std::runtime_error{"Cannot increment"};
	}
	void LtnVM::dec() {
		FETCH
		if(isInt(x)) {
			return this->reg.push({x.i - 1});
		}
		if(isFloat(x)) {
			return this->reg.push({x.f - 1});
		}
		throw std::runtime_error{"Cannot decrement"};
	}

	#undef FETCH
}