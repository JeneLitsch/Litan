#include "chrono.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/inst/instructions.hxx"

namespace ltn::vm::stdlib {
	Value clock_new::func(Context * context, const Value * args)  {
		VMCore & core = *static_cast<VMCore*>(context->core);
		core.heap.collect_garbage(core.stack);
		return value::clock(core.heap.make<Clock>());
	}



	Value clock_is::func(Context * context, const Value * args)  {
		return value::boolean(is_clock(args[0]));
	}



	Value clock_cast::func(Context * context, const Value * args)  {
		return is_clock(args[0]) ? args[0] : value::null;
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