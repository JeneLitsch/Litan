#include "math.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/convert.hxx"

namespace ltn::vm::build_in {
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