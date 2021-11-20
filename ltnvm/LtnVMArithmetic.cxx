#include "LtnVM.hxx"
#include <cmath>
#include "TypeCheck.hxx"

namespace ltn::vm {

	#define FETCH\
		const auto r = this->reg.pop();\
		const auto l = this->reg.pop();

	#define BIN_II(op)\
		if(isInt(l) && isInt(r)) {\
			return this->reg.push(Value{l.i op r.i});\
		}

	#define BIN_FF(op)\
		if(isInt(l) && isInt(r)) {\
			return this->reg.push(Value{l.i op r.i});\
		}

	#define BIN_FX_FF(op)\
		if(isInt(l) && isInt(r)) {\
			return this->reg.push(Value{op(l.i, r.i)});\
		}

	void LtnVM::add() { 
		FETCH
		BIN_II(+)
		BIN_FF(+)
		throw std::runtime_error{"Cannot add types"};
	}
	void LtnVM::sub() {
		FETCH
		BIN_II(-)
		BIN_FF(-)
		throw std::runtime_error{"Cannot subtract types"};
	}
	void LtnVM::mlt() {
		FETCH
		BIN_II(*)
		BIN_FF(*)
		throw std::runtime_error{"Cannot multiply types"};
	}
	void LtnVM::div() {
		FETCH
		BIN_II(/)
		BIN_FF(/)
		throw std::runtime_error{"Cannot divide types"};
	}
	void LtnVM::mod() {
		FETCH
		BIN_II(%)
		BIN_FX_FF(std::fmod)
		throw std::runtime_error{"Cannot mod types"};
	}

	#undef FETCH
	#undef BIN_II
	#undef BIN_FF
	#undef BIN_FX_FF
}