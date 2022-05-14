#include "LtnVM.hxx"
#include <cmath>
#include "type_check.hxx"
#include <sstream>
#include "Operations.hxx"
#include "calcBinary.hxx"
#include "convert.hxx"

#define FETCH\
	const auto r = this->reg.pop();\
	const auto l = this->reg.pop();

namespace ltn::vm {
	void LtnVM::shift_l() {
		FETCH
		const auto value = convert::to_int(l) << convert::to_int(r);
		return this->reg.push(Value{value});
	}

	void LtnVM::shift_r() {
		FETCH
		const auto value = convert::to_int(l) >> convert::to_int(r);
		return this->reg.push(Value{value});
	}

	void LtnVM::bit_and() {
		FETCH
		const auto value = convert::to_int(l) & convert::to_int(r);
		return this->reg.push(Value{value});
	}


	void LtnVM::bit_or() {
		FETCH
		const auto value = convert::to_int(l) | convert::to_int(r);
		return this->reg.push(Value{value});
	}

	
	void LtnVM::bit_xor() {
		FETCH
		const auto value = convert::to_int(l) ^ convert::to_int(r);
		return this->reg.push(Value{value});
	}

	void LtnVM::bit_not() {
		const auto x = this->reg.pop();
		return this->reg.push(Value{~convert::to_int(x)});
	}
}
#undef FETCH