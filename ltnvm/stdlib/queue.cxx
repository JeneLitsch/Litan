#include "queue.hxx"
#include "ltnvm/objects/container/Queue.hxx"

namespace ltn::vm::stdlib {
	Value queue_size::func(Context *, const Value * args) {
		Queue * queue = req_queue(args + 0);
		return value::integer(queue->size());
	}

	Value queue_is_empty::func(Context * context, const Value * args) {
		return value::boolean(queue_size::func(context, args).i == 0);
	}
}