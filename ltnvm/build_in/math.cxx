#include "math.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/convert.hxx"
#include "ltnvm/cast.hxx"
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



	Value min(VmCore & core) {
		auto a = core.reg.pop();
		auto b = core.reg.pop();
		return compare(a, b, core.heap) <= 0 ? a : b;
	}



	Value max(VmCore & core) {
		auto a = core.reg.pop();
		auto b = core.reg.pop();
		return compare(a, b, core.heap) >= 0 ? a : b;
	}



	Value clamp(VmCore & core) {
		auto max = core.reg.pop();
		auto min = core.reg.pop();
		auto val = core.reg.pop();

		if(compare(val, min, core.heap) < 0) {
			return min;
		}

		if(compare(val, max, core.heap) > 0) {
			return max;
		}

		return val;
	}



	Value round(VmCore & core) {
		return rounding<Round>(core.reg.pop());
	}



	Value floor(VmCore & core) {
		return rounding<Floor>(core.reg.pop());
	}



	Value ceil(VmCore & core) {
		return rounding<Ceil>(core.reg.pop());
	}
}