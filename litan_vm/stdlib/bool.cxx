#include "bool.hxx"
#include "litan_vm/utils/cast.hxx"


namespace ltn::vm::stdlib {
	Value boolean_new::func(ltn_Context * context, const Value * args) {
		return value::boolean(false);
	}



	Value boolean_is::func(ltn_Context * context, const Value * args) {
		return value::boolean(is_bool(args[0]));
	}



	Value boolean_cast::func(ltn_Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		return value::boolean(cast::to_bool(args[0], *core));
	}
}
