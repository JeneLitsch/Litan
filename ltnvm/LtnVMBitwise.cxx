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
		if(is_int(l) && is_int(r)) {
			return this->reg.push(Value{l.i << r.i});
		}
		throw except::invalid_operands();
	}

	void LtnVM::shift_r() {
		FETCH
		if(is_int(l) && is_int(r)) {
			return this->reg.push(Value{l.i >> r.i});
		}
		throw except::invalid_operands();
	}

	void LtnVM::bit_and() {
		FETCH
		if(is_int(l) && is_int(r)) {
			return this->reg.push(Value{l.i & r.i});
		}
		throw except::invalid_operands();
	}


	void LtnVM::bit_or() {
		FETCH
		if(is_int(l) && is_int(r)) {
			return this->reg.push(Value{l.i | r.i});
		}
		throw except::invalid_operands();
	}

	
	void LtnVM::bit_xor() {
		FETCH
		if(is_int(l) && is_int(r)) {
			return this->reg.push(Value{l.i ^ r.i});
		}
		throw except::invalid_operands();
	}
}
#undef FETCH