#include "iter.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/utils/convert.hxx"
#include "litan_vm/inst/instructions.hxx"
#include "litan_vm/objects/iter.hxx"

namespace ltn::vm::build_in::iter {
	Value range(VMCore & core) {
		auto step = convert::to_int(core.stack.pop());
		auto end = convert::to_int(core.stack.pop());
		auto begin = convert::to_int(core.stack.pop());
		auto ptr = core.heap.make<RangeIterator>(begin, end, step);
		return value::iterator(ptr);
	}



	Value next(VMCore & core) {
		return iterator::next(core.stack.pop());
	}



	Value get(VMCore & core) {
		return iterator::get(core.stack.pop());
	}



	Value move(VMCore & core) {
		const auto step = core.stack.pop();
		const auto iter = core.stack.pop();
		iterator::move(iter, step);
		return value::null;
	}



	Value iter(VMCore & core) {
		return iterator::wrap(core.stack.pop(), core);
	}



	Value is_stop(VMCore & core) {
		return value::boolean(is_iterator_stop(core.stack.pop()));
	}



	Value combined(VMCore & core) {
		auto param = core.stack.pop();
		if(!is_array(param) && !is_tuple(param)) {
			throw except::invalid_argument();
		}
		Contiguous * arr = value::as<Contiguous>(param);
		std::vector<Iterator *> iters;
		for(auto & e : *arr) {
			iters.push_back(value::as<Iterator>(iterator::wrap(e, core)));
		}
		auto ptr =  core.heap.make<CombinedIterator>(std::move(iters), &core.heap);
		return value::iterator(ptr);
	}



	Value reversed(VMCore & core) {
		auto ref = iterator::wrap(core.stack.pop(), core);
		auto ptr = core.heap.make<ReversedIterator>(ref);
		return value::iterator(ptr);
	}
}