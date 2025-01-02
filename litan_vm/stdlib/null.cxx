#include "null.hxx"
#include "litan_vm/utils/cast.hxx"

namespace ltn::vm::stdlib {
	Value null_new::func(ltn_Context * context, const Value * args) {
		return value::null;
	}



	Value null_is::func(ltn_Context * context, const Value * args) {
		return value::boolean(is_null(args[0]));
	}



	Value null_cast::func(ltn_Context *, const Value *) {
		return value::null;
	}
}