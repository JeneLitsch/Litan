#include "algorithm.hxx"
#include "ltnvm/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/stringify.hxx"

namespace ltn::vm::build_in {
	Value pop(VmCore & core) {
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref.u);
			if(std::empty(container)) throw except::out_of_range();
			const auto elem = container.back();
			container.pop_back();
			return elem;
		}

		if(is_string(ref)) {
			auto & container = core.heap.read<String>(ref.u);
			if(std::empty(container)) throw except::out_of_range();
			const auto elem = container.back();
			container.pop_back();
			return value::character(elem);
		}

		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			if(std::empty(container)) throw except::out_of_range();
			const auto elem = container.back();
			container.pop_back();
			return elem;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			if(std::empty(container)) throw except::out_of_range();
			const auto elem = container.front();
			container.pop_front();
			return elem;
		}
	
		throw except::invalid_argument();
	}
}