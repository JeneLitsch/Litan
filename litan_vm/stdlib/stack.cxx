#include "stack.hxx"
#include "litan_vm/objects/container/Stack.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/VMCore.hxx"

namespace ltn::vm::stdlib {

	Value stack_new::func(Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		core->heap.collect_garbage(core->stack);
		return value::stack(core->heap.make<Stack>());
	}



	Value stack_size::func(Context *, const Value * args) {
		Stack * stack = req_stack(args + 0);
		return value::integer(stack->size());
	}



	Value stack_is_empty::func(Context * context, const Value * args) {
		return value::boolean(stack_size::func(context, args).i == 0);
	}



	Value stack_push::func(Context *, const Value * args) {
		Stack * stack = req_stack(args + 0);
		stack->push_back(args[1]);
		return value::null;
	}



	Value stack_pop::func(Context *, const Value * args) {
		Stack * stack = req_stack(args + 0);
		if (std::empty(*stack)) throw except::out_of_range();
		Value value = stack->unsafe_back();
		stack->unsafe_pop_back();
		return value;
	}



	Value stack_values::func(Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		Stack * stack = req_stack(args + 0);
		const std::deque<Value> & deque = stack->get_underlying();
		Array * array = core->heap.make<Array>(std::vector<Value>{std::begin(deque), std::end(deque)});
		return value::array(array);
	}
}