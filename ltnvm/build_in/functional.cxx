#include "functional.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::build_in {
	Value arity(VmCore & core) {
		const auto ref = core.reg.pop();
		if(is_fxptr(ref)) {
			const auto & fxptr = core.heap.read<FxPointer>(ref.u);
			return value::integer(static_cast<std::int64_t>(fxptr.params));
		}

		throw except::invalid_argument("std::arity expected a function pointer");
	}
}