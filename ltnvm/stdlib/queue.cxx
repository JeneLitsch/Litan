#include "queue.hxx"
#include "ltnvm/objects/container/Queue.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::stdlib {
	Value queue_size::func(Context *, const Value * args) {
		Queue * queue = req_queue(args + 0);
		return value::integer(queue->size());
	}

	Value queue_is_empty::func(Context * context, const Value * args) {
		return value::boolean(queue_size::func(context, args).i == 0);
	}

	Value queue_push::func(Context * context, const Value * args) {
		Queue * queue = req_queue(args + 0);
		queue->push_back(args[1]);
		return value::null;
	}

	Value queue_pop::func(Context * context, const Value * args) {
		Queue * queue = req_queue(args + 0);
		if (std::empty(*queue)) throw except::out_of_range();
		Value value = queue->unsafe_front();
		queue->pop_front();
		return value;
	}

	Value queue_values::func(Context * context, const Value * args) {
		VMCore * core = static_cast<VMCore *>(context->core);
		Queue * queue = req_queue(args + 0);
		const std::deque<Value> & deque = queue->get_underlying();
		Array * array = core->heap.make<Array>(std::vector<Value>{std::begin(deque), std::end(deque)});
		return value::array(array);
	}
}