#include "chrono.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/inst/instructions.hxx"

namespace ltn::vm::stdlib {
	Value clock::func(Context * context, const Value * args)  {
		VMCore & core = *static_cast<VMCore*>(context->core);
		core.heap.collect_garbage(core.stack);
		return value::clock(core.heap.make<Clock>());
	}



	Value to_seconds::func(Context *, const Value * args) {
		if(!is_clock(args[0])) throw except::invalid_argument("Not a clock");
		Clock * clock = value::as<Clock>(args[0]);
		return value::floating(clock->getSeconds());
	}



	Value to_milliseconds::func(Context * context, const Value * args)  {
		return value::floating(to_seconds::func(context, args).f * 1000.0);
	}
}