#include "math.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/utils/cast.hxx"
#include "ltnvm/MathFunctions.hxx"

namespace ltn::vm::build_in {
	template<class Fx>
	Value rounding(const Value & value) {
		constexpr Fx fx{};
		if(is_float(value)) {
			return Value{fx(value.f)};
		}
		if(is_int(value) || is_bool(value) || is_char(value)) {
			return cast::to_int(value);
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



	Value min(VmCore & core) {
		auto a = core.stack.pop();
		auto b = core.stack.pop();
		return compare(a, b, core) <= 0 ? a : b;
	}



	Value max(VmCore & core) {
		auto a = core.stack.pop();
		auto b = core.stack.pop();
		return compare(a, b, core) >= 0 ? a : b;
	}



	Value clamp(VmCore & core) {
		auto max = core.stack.pop();
		auto min = core.stack.pop();
		auto val = core.stack.pop();

		if(compare(val, min, core) < 0) {
			return min;
		}

		if(compare(val, max, core) > 0) {
			return max;
		}

		return val;
	}



	Value round(VmCore & core) {
		return rounding<Round>(core.stack.pop());
	}



	Value floor(VmCore & core) {
		return rounding<Floor>(core.stack.pop());
	}



	Value ceil(VmCore & core) {
		return rounding<Ceil>(core.stack.pop());
	}



	Value abs(VmCore & core) {
		return function<Absolute>(core.stack.pop());
	}



	Value sin(VmCore & core) {
		return function<Sinus>(core.stack.pop());
	}



	Value cos(VmCore & core) {
		return function<Cosinus>(core.stack.pop());
	}



	Value tan(VmCore & core) {
		return function<Tangents>(core.stack.pop());
	}



	Value sqrt(VmCore & core) {
		const auto value = core.stack.pop();
		return std::sqrt(convert::to_float(value));
	}
	


	Value hypot(VmCore & core) {
		const auto r = core.stack.pop();
		const auto l = core.stack.pop();
		return std::hypot(
			convert::to_float(l),
			convert::to_float(r));
	}



	Value log(VmCore & core){
		const auto r = core.stack.pop();
		const auto l = core.stack.pop();
		return std::log(convert::to_float(l))
			/ std::log(convert::to_float(r));
	}
	

	
	Value ln(VmCore & core) {
		const auto value = core.stack.pop();
		return std::log(convert::to_float(value));
	}



	Value ld(VmCore & core) {
		core.stack.push(value::floating(2));
		return log(core);
	}



	Value lg(VmCore & core) {
		core.stack.push(value::floating(10));
		return log(core);
	}
}