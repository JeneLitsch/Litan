#include "struct.hxx"
#include "litan_vm/objects/container/Struct.hxx"
#include "litan_vm/VMCore.hxx"
#include "litan_vm/utils/stringify.hxx"
#include "litan_core/utf8.hxx"

namespace ltn::vm::stdlib {
	Value struct_new::func(Context * context, const Value *) {
		VMCore * core = static_cast<VMCore*>(context->core);
		core->heap.collect_garbage(core->stack);
		return value::strukt(core->heap.make<Struct>());
	}



	Value struct_is::func(Context *, const Value * args) {
		return value::boolean(is_struct(args[0]));
	}


	Value struct_cast::func(Context * context, const Value * args) {
		return is_struct(args[0]) ? args[0] : value::null;
	}

}