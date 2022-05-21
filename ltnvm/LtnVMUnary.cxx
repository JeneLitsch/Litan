#include "LtnVM.hxx"
#include "type_check.hxx"
#include "convert.hxx"


namespace ltn::vm {
	#define FETCH const auto x = this->core.reg.pop();

	void LtnVM::neg() {
		FETCH
		if(is_bool(x)) {
			return this->core.reg.push({- static_cast<std::int64_t>(x.b)});
		}
		if(is_char(x)) {
			return this->core.reg.push({- static_cast<std::int64_t>(x.c)});
		}
		if(is_int(x)) {
			return this->core.reg.push({- x.i});
		}
		if(is_float(x)) {
			return this->core.reg.push({- x.f});
		}
		throw except::invalid_argument();
	}
	void LtnVM::n0t() {
		FETCH
		return this->core.reg.push(!convert::to_bool(x));
	}

	void LtnVM::inc() {
		FETCH
		if(is_int(x)) {
			return this->core.reg.push({x.i + 1});
		}
		if(is_float(x)) {
			return this->core.reg.push({x.f + 1});
		}
		throw except::invalid_argument();
	}
	void LtnVM::dec() {
		FETCH
		if(is_int(x)) {
			return this->core.reg.push({x.i - 1});
		}
		if(is_float(x)) {
			return this->core.reg.push({x.f - 1});
		}
		throw except::invalid_argument();
	}

	#undef FETCH
}