#include "iter.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/inst/instructions.hxx"

namespace ltn::vm::build_in::iter {
	Value range(VmCore & core) {
		auto step = convert::to_int(core.stack.pop());
		auto end = convert::to_int(core.stack.pop());
		auto begin = convert::to_int(core.stack.pop());
		auto ptr = core.heap.track(iterator::range(begin, end, step));
		return value::iterator(ptr);
	}



	Value next(VmCore & core) {
		return iterator::next(core.stack.pop());
	}



	Value get(VmCore & core) {
		return iterator::get(core.stack.pop());
	}



	Value move(VmCore & core) {
		const auto step = core.stack.pop();
		const auto iter = core.stack.pop();
		iterator::move(iter, step);
		return value::null;
	}



	Value iter(VmCore & core) {
		return iterator::wrap(core.stack.pop(), core.heap);
	}



	Value is_stop(VmCore & core) {
		return value::boolean(is_iterator_stop(core.stack.pop()));
	}



	Value combined(VmCore & core) {
		auto param = core.stack.pop();
		if(!is_array(param) && !is_tuple(param)) {
			throw except::invalid_argument();
		}
		auto & arr = core.heap.read<Array>(param);
		std::vector<Value> refs;
		for(auto & e : arr) {
			refs.push_back(iterator::wrap(e, core.heap));
		}
		auto ptr = core.heap.track(iterator::combined(std::move(refs), core.heap));
		return value::iterator(ptr);
	}



	Value reversed(VmCore & core) {
		auto ref = iterator::wrap(core.stack.pop(), core.heap);
		return value::iterator(core.heap.track(iterator::reversed(ref)));
	}
}