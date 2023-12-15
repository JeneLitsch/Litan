#include "functional.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/inst/instructions.hxx"

namespace ltn::vm::build_in {
	Value arity(VMCore & core) {
		const auto ref = core.stack.pop();
		if(is_fxptr(ref)) {
			const auto & fxptr = core.heap.read<FxPointer>(ref);
			return value::integer(static_cast<std::int64_t>(fxptr.params));
		}

		throw except::invalid_argument("std::arity expected a function pointer");
	}



	Value invoke(VMCore & core) {
		inst::invoke_variadic(core);
		return core.stack.pop();
	}



	Value is_variadic(VMCore & core) {
		const auto ref = core.stack.pop();
		if(is_fxptr(ref)) {
			const auto & fxptr = core.heap.read<FxPointer>(ref);
			return value::boolean(fxptr.is_variadic);
		}
		throw except::invalid_argument("std::is_variadic expected a function pointer");
	}



	Value noroutine(VMCore & core) {
		return value::noroutine;
	}



	Value is_noroutine(VMCore & core) {
		return value::boolean(ltn::vm::is_noroutine(core.stack.pop()));
	}
}