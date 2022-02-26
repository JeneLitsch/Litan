#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "convert.hxx"


namespace ltn::vm {
	#define FETCH const auto x = this->reg.pop();

	void LtnVM::neg() {
		FETCH
		if(is_bool(x)) {
			return this->reg.push({- static_cast<std::int64_t>(x.b)});
		}
		if(is_char(x)) {
			return this->reg.push({- static_cast<std::int64_t>(x.c)});
		}
		if(is_int(x)) {
			return this->reg.push({- x.i});
		}
		if(is_float(x)) {
			return this->reg.push({- x.f});
		}
		throw except::invalid_argument();
	}
	void LtnVM::n0t() {
		FETCH
		return this->reg.push(!convert::to_bool(x));
	}

	void LtnVM::inc() {
		FETCH
		if(is_int(x)) {
			return this->reg.push({x.i + 1});
		}
		if(is_float(x)) {
			return this->reg.push({x.f + 1});
		}
		throw except::invalid_argument();
	}
	void LtnVM::dec() {
		FETCH
		if(is_int(x)) {
			return this->reg.push({x.i - 1});
		}
		if(is_float(x)) {
			return this->reg.push({x.f - 1});
		}
		throw except::invalid_argument();
	}

	#undef FETCH
}