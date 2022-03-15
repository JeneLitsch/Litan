#include "LtnVM.hxx"
#include "type_check.hxx"
#include <cmath>
#include "MathFunctions.hxx"
#include "convert.hxx"

namespace ltn::vm {
	#define FETCH\
		const auto r = this->reg.pop();\
		const auto l = this->reg.pop();


	bool less(const Value & l, const Value & r) {
		return convert::to_float(l) <= convert::to_float(r);
	}


	template<class Fx>
	Value rounding(const Value & value) {
		constexpr Fx fx{};
		if(is_float(value)) {
			return Value{fx(value.f)};
		}
		if(is_int(value) || is_bool(value) || is_char(value)) {
			return value;
		}
		throw except::invalid_argument();
	}


	template<class Fx>
	Value function(const Value & value) {
		constexpr Fx fx{};
		if(is_float(value)) {
			return Value{fx(value.f)};
		}
		if(is_int(value)) {
			return Value{fx(value.i)};
		}
		if(is_bool(value)) {
			return Value{fx(value.b)};
		}
		if(is_char(value)) {
			return Value{fx(value.c)};
		}
		throw except::invalid_argument();
	}


	void LtnVM::min() {
		FETCH
		const auto less = compare(l, r, this->heap) < 0;
		this->reg.push(less ? l : r);
	}


	void LtnVM::max() {
		FETCH
		const auto more = compare(l, r, this->heap) > 0;
		this->reg.push(more ? l : r);
	}


	void LtnVM::round() {
		this->reg.push(rounding<Round>(this->reg.pop()));
	}


	void LtnVM::floor() {
		this->reg.push(rounding<Floor>(this->reg.pop()));
	}


	void LtnVM::ceil() {
		this->reg.push(rounding<Ceil>(this->reg.pop()));
	}


	void LtnVM::abs() {
		this->reg.push(function<Absolute>(this->reg.pop()));
	}


	void LtnVM::hypot() {
		FETCH
		this->reg.push(std::hypot(
			convert::to_float(l),
			convert::to_float(r)));
	}


	void LtnVM::sqrt() {
		const auto value = this->reg.pop();
		this->reg.push(std::sqrt(convert::to_float(value)));
	}


	void LtnVM::log() {
		FETCH
		const auto result 
			= std::log(convert::to_float(l))
			/ std::log(convert::to_float(r));
		this->reg.push(result);
	}


	void LtnVM::ln() {
		const auto value = this->reg.pop();
		this->reg.push(std::log(convert::to_float(value)));
	}


	void LtnVM::pow() {
		FETCH
		const auto b = convert::to_float(l);
		const auto e = convert::to_float(r);
		this->reg.push(std::pow(b, e));
	}
	

	void LtnVM::sin() {
		this->reg.push(function<Sinus>(this->reg.pop()));
	}


	void LtnVM::cos() {
		this->reg.push(function<Cosinus>(this->reg.pop()));
	}


	void LtnVM::tan() {
		this->reg.push(function<Tangents>(this->reg.pop()));
	}
	

	#undef FETCH
}