#include "container.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/native/native.hxx"
#include "ltnvm/stdlib/stack.hxx"
#include "ltnvm/stdlib/queue.hxx"
#include "ltnvm/stdlib/array.hxx"

namespace ltn::vm::build_in {
	Value push(VMCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_array(ref)) return call<stdlib::array_push>(core, { ref, elem });
		if(is_stack(ref)) return call<stdlib::stack_push>(core, { ref, elem });
		if(is_queue(ref)) return call<stdlib::queue_push>(core, { ref, elem });
		
		throw except::invalid_argument();
	}
}