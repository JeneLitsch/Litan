#include "stack.hxx"
#include "ltnvm/objects/container/Stack.hxx"

namespace ltn::vm::stdlib {
	Value stack_size::func(Context *, const Value * args) {
		Stack * stack = req_stack(args + 0);
		return value::integer(stack->size());
	}

	Value stack_is_empty::func(Context * context, const Value * args) {
		return value::boolean(stack_size::func(context, args).i == 0);
	}
}