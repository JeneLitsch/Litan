#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/native/native.hxx"
#include "ltnvm/stdlib/stack.hxx"
#include "ltnvm/stdlib/queue.hxx"

namespace ltn::vm::build_in {
	Value pop(VMCore & core) {
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			Array * container = value::as<Array>(ref);
			if(std::empty(*container)) throw except::out_of_range();
			const auto elem = container->unsafe_back();
			container->unsafe_pop_back();
			return elem;
		}

		if(is_stack(ref)) return call<stdlib::stack_pop>(core, { ref });
		if(is_queue(ref)) return call<stdlib::queue_pop>(core, { ref });
	
		throw except::invalid_argument();
	}
}