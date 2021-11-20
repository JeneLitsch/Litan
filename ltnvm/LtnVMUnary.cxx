#include "LtnVM.hxx"
#include "TypeCheck.hxx"



namespace ltn::vm {
	#define FETCH const auto x = this->reg.pop();

	void LtnVM::neg() {
		FETCH
		if(isInt(x)) {
			this->reg.push({- x.i});
		}
		if(isFloat(x)) {
			this->reg.push({- x.f});
		}
		throw std::runtime_error{"Cannot negate"};
	}
	void LtnVM::n0t() {
		FETCH
		if(isBool(x)) {
			this->reg.push({!x.b});
		}
		throw std::runtime_error{"Cannot apply not"};
	}

	#undef FETCH
}