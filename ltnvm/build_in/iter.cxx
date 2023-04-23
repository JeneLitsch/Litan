#include "iter.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/convert.hxx"
#include "ltnvm/inst/instructions.hxx"

namespace ltn::vm::build_in::iter {
	Value range(VmCore & core) {
		auto step = convert::to_int(core.stack.pop());
		auto end = convert::to_int(core.stack.pop());
		auto begin = convert::to_int(core.stack.pop());
		auto ptr = core.heap.alloc(iterator::range(begin, end, step));
		return value::iterator(ptr);
	}



	Value next(VmCore & core) {
		inst::next(core);
		return core.stack.pop();
	}



	Value iter(VmCore & core) {
		inst::iter(core);
		return core.stack.pop();
	}
}