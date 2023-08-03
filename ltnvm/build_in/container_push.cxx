#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	Value push(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref);
			container.push_back(elem);
			return value::null;
		}

		if(is_stack(ref)) {
			auto & container = core.heap.read<Segmented>(ref);
			container.data.push_back(elem);
			return value::null;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Segmented>(ref);
			container.data.push_back(elem);
			return value::null;
		}
		
		throw except::invalid_argument();
	}
}