#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <cmath>
#include "MathFunctions.hxx"
namespace ltn::vm {
	#define FETCH\
		const auto r = this->reg.pop();\
		const auto l = this->reg.pop();

	double toDouble(const Value & value) {
		if(isBool(value)) return static_cast<double>(value.b);
		if(isInt(value)) return static_cast<double>(value.i);
		if(isFloat(value)) return static_cast<double>(value.f);
		throw std::runtime_error {"Expected numeric type"};
	}

	bool less(const Value & l, const Value & r) {
		return toDouble(l) < toDouble(r);
	}

	template<class Fx>
	Value rounding(const Value & value, const auto & msg) {
		constexpr Fx fx{};
		if(isFloat(value)) {
			return Value{fx(value.f)};
		}
		if(isInt(value) || isBool(value)) {
			return value;
		}
		throw std::runtime_error{msg};
	}

	template<class Fx>
	Value function(const Value & value, const auto & msg) {
		constexpr Fx fx{};
		if(isFloat(value)) {
			return Value{fx(value.f)};
		}
		if(isInt(value)) {
			return Value{fx(value.i)};
		}
		if(isBool(value)) {
			return Value{fx(value.b)};
		}
		throw std::runtime_error{msg};
	}
	
	void LtnVM::min() {
		FETCH
		this->reg.push((less(l, r) ? l : r));
	}
	void LtnVM::max() {
		FETCH
		this->reg.push((less(l, r) ? r : l));
	}
	void LtnVM::round() {
		constexpr auto msg = "Can only round numeric types";
		this->reg.push(rounding<Round>(this->reg.pop(), msg));
	}
	void LtnVM::floor() {
		constexpr auto msg = "Can only floor numeric types";
		this->reg.push(rounding<Floor>(this->reg.pop(), msg));
	}
	void LtnVM::ceil() {
		constexpr auto msg = "Can only ceil numeric types";
		this->reg.push(rounding<Ceil>(this->reg.pop(), msg));
	}
	void LtnVM::abs() {
		constexpr auto msg = "Can only take abs() from numeric types";
		this->reg.push(function<Absolute>(this->reg.pop(), msg));
	}
	
	void LtnVM::sin() {
		constexpr auto msg = "sin() only accepts numeric types";
		this->reg.push(function<Sinus>(this->reg.pop(), msg));
	}
	void LtnVM::cos() {
		constexpr auto msg = "cos() only accepts numeric types";
		this->reg.push(function<Cosinus>(this->reg.pop(), msg));
	}
	void LtnVM::tan() {
		constexpr auto msg = "tan() only accepts numeric types";
		this->reg.push(function<Tangents>(this->reg.pop(), msg));
	}

	#undef FETCH
}