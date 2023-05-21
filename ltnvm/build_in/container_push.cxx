#include "algorithm.hxx"
#include "ltnvm/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/stringify.hxx"

namespace ltn::vm::build_in {
	Value push(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref.u);
			container.push_back(elem);
			return value::null;
		}

		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			container.push_back(elem);
			return value::null;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			container.push_back(elem);
			return value::null;
		}
		
		throw except::invalid_argument();
	}
}