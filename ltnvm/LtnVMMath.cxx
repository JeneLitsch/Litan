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
		return toDouble(l) <= toDouble(r);
	}

	template<class Fx>
	Value rounding(const Value & value) {
		constexpr Fx fx{};
		if(isFloat(value)) {
			return Value{fx(value.f)};
		}
		if(isInt(value) || isBool(value)) {
			return value;
		}
		throw except::invalidArgument();
	}

	template<class Fx>
	Value function(const Value & value) {
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
		throw except::invalidArgument();
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
		this->reg.push(std::hypot(toDouble(l), toDouble(r)));
	}
	void LtnVM::sqrt() {
		const auto value = this->reg.pop();
		this->reg.push(std::sqrt(toDouble(value)));
	}
	void LtnVM::log() {
		FETCH
		const auto result = std::log(toDouble(l)) / std::log(toDouble(r));
		this->reg.push(result);
	}
	void LtnVM::ln() {
		const auto value = this->reg.pop();
		this->reg.push(std::log(toDouble(value)));
	}
	void LtnVM::pow() {
		FETCH
		const auto b = toDouble(l);
		const auto e = toDouble(r);
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