#include "chrono.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/inst/instructions.hxx"

namespace ltn::vm::build_in::chrono {
	Value clock(VmCore & core) {
		inst::newclock(core);
		return core.stack.pop();
	}



	Value to_seconds(VmCore & core) {
		auto ref = core.stack.pop();
		if(!is_clock(ref)) throw except::invalid_argument("Not a clock");
		auto & clock = core.heap.read<Clock>(ref.u);
		return value::floating(clock.getSeconds());
	}



	Value to_milliseconds(VmCore & core) {
		return value::floating(to_seconds(core).f * 1000.0);
	}
}