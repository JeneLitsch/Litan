#include "functional.hxx"
#include "litan_vm/inst/instructions.hxx"
#include "litan_vm/utils/function.hxx"

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
		const Value ref_args = args[1];
		const Value ref_fx = args[0];
		if(is_array(ref_args) || is_tuple(ref_args)) {
			const auto & args = *value::as<Contiguous>(ref_args);
			const auto arity = std::size(args);

			load_onto_stack(core.stack, args);
			invoke_function(core, ref_fx, arity);
			return core.stack.pop();
		}
		else throw except::invalid_argument();
	}



	Value function_is_variadic::func(Context * context, const Value * args) {
		if(is_fxptr(args[0])) {
			const FunctionPointer * fxptr = value::as<FunctionPointer>(args[0]);
			return value::boolean(fxptr->is_variadic);
		}
		throw except::invalid_argument("std::is_variadic expected a function pointer");
	}
}