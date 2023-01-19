#include "instructions.hxx"

namespace ltn::vm::inst {
	void deref(VmCore & core) {
		if(is_null(core.stack.peek())) {
			throw Exception {
				.type = Exception::Type::INVALID_ARGUMENT,
				.msg = "Cannot dereference null"
			};
		}
	}
}