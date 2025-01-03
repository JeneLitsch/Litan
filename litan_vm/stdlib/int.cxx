#include "int.hxx"
#include "litan_vm/utils/cast.hxx"

namespace ltn::vm::stdlib {
	Value integer_new::func(ltn_Context * context, const Value * args) {
		return value::integer(0);
	}



	Value integer_is::func(ltn_Context * context, const Value * args) {
		return value::boolean(is_int(args[0]));
	}


	Value integer_cast::func(ltn_Context * context, const Value * args) {
		return value::integer(cast::to_int(args[0]));
	}
}