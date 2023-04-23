#include "iter.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/convert.hxx"

namespace ltn::vm::build_in::iter {
	Value range(VmCore & core) {
		auto step = convert::to_int(core.stack.pop());
		auto end = convert::to_int(core.stack.pop());
		auto begin = convert::to_int(core.stack.pop());
		auto ptr = core.heap.alloc(iterator::range(begin, end, step));
		return value::iterator(ptr);
	}



	namespace {
		Value next_range(Iterator::Range & range) {
			if(range.current >= range.begin && range.current < range.end) {
				auto prev = range.current;
				range.current += range.step;
				return value::integer(prev);
			}
			else {
				return value::null;
			}
		}
	}


	Value next(VmCore & core) {
		auto ref = core.stack.pop();
		if(!is_iterator(ref)) {
			throw except::invalid_argument("std::next expects an iterator");
		}
		auto & iter = core.heap.read<Iterator>(ref);
		
		switch (iter.type) {
			case Iterator::Type::RANGE: return next_range(iter.range);
		}

	}
}