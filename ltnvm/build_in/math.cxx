#include "math.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/convert.hxx"

namespace ltn::vm::build_in {
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
}