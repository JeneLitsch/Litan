#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	Value peek(VmCore & core) {
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref);
			if(std::empty(container)) throw except::out_of_range();
			const auto elem = container.data.back();
			return elem;
		}

		if(is_string(ref)) {
			auto & container = core.heap.read<String>(ref);
			if(std::empty(container.data)) throw except::out_of_range();
			const auto elem = container.data.back();
			return value::character(elem);
		}


		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref);
			if(std::empty(container.data)) throw except::out_of_range();
			const auto elem = container.data.back();
			return elem;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref);
			if(std::empty(container.data)) throw except::out_of_range();
			const auto elem = container.data.front();
			return elem;
		}

		throw except::invalid_argument();
	}
}