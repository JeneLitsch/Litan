#include "instructions.hxx"
#include "litan_vm/utils/function.hxx"

namespace ltn::vm::inst {
	void invoke(VMCore & core) {
		const auto arity = core.fetch_byte();
		const auto ref_fx = core.stack.pop();

		invoke_function(core, ref_fx, arity);
	}



	void invoke_variadic(VMCore & core) {
		const auto ref_args = core.stack.pop();
		const auto ref_fx = core.stack.pop();
		if(is_array(ref_args) || is_tuple(ref_args)) {
			const auto & args = *value::as<Contiguous>(ref_args);
			const auto arity = std::size(args);

			load_onto_stack(core.stack, args);
			if(is_script_function(ref_fx)) {
				return invoke_script_function(core, ref_fx, arity);
			}
			else throw except::invalid_argument("Callable must be native or script function");
		}
		else throw except::invalid_argument();
	}
}