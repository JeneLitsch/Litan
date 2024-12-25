#include "functional.hxx"
#include "litan_vm/inst/instructions.hxx"

namespace ltn::vm::stdlib {
	Value function_arity::func(Context * context, const Value * args) {
		if(is_fxptr(args[0])) {
			const auto * fxptr = value::as<FunctionPointer>(args[0]);
			return value::integer(static_cast<std::int64_t>(fxptr->params));
		}

		throw except::invalid_argument("std::arity expected a function pointer");
	}
	
	
	
	Value function_call::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		core.stack.push(args[0]);
		core.stack.push(args[1]);
		inst::invoke_variadic(core);
		return core.stack.pop();
	}



	Value function_is_variadic::func(Context * context, const Value * args) {
		if(is_fxptr(args[0])) {
			const FunctionPointer * fxptr = value::as<FunctionPointer>(args[0]);
			return value::boolean(fxptr->is_variadic);
		}
		throw except::invalid_argument("std::is_variadic expected a function pointer");
	}
}