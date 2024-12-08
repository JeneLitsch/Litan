#include "chrono.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/inst/instructions.hxx"

namespace ltn::vm::build_in::chrono {
	Value clock(VMCore & core) {
		inst::newclock(core);
		return core.stack.pop();
	}



	Value to_seconds(VMCore & core) {
		auto ref = core.stack.pop();
		if(!is_clock(ref)) throw except::invalid_argument("Not a clock");
		Clock * clock = value::as<Clock>(ref);
		return value::floating(clock->getSeconds());
	}



	Value to_milliseconds(VMCore & core) {
		return value::floating(to_seconds(core).f * 1000.0);
	}
}