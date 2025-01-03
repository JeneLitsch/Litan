#include "float.hxx"
#include "litan_vm/utils/cast.hxx"

namespace ltn::vm::stdlib {
	Value floating_new::func(ltn_Context * context, const Value * args) {
		return value::floating(0.0);
	}



	Value floating_is::func(ltn_Context * context, const Value * args) {
		return value::boolean(is_float(args[0]));
	}


	
	Value floating_cast::func(ltn_Context * context, const Value * args) {
		return value::floating(cast::to_float(args[0]));
	}
}