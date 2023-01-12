#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <iostream>


namespace ltn::vm::inst {
	void type_id(VmCore & core) {
		const auto value = core.stack.pop();
		core.stack.push(Value{static_cast<std::int64_t>(value.type)});
	}



	void clone(VmCore & core) {
		const auto ref = core.stack.pop();
		if(is_array(ref)) core.stack.push(Value{core.heap.clone<Array>(ref.u), ref.type});
		if(is_string(ref)) core.stack.push(Value{core.heap.clone<String>(ref.u), ref.type});
		if(is_stack(ref)) core.stack.push(Value{core.heap.clone<Deque>(ref.u), ref.type});
		if(is_queue(ref)) core.stack.push(Value{core.heap.clone<Deque>(ref.u), ref.type});
		if(is_map(ref)) core.stack.push(Value{core.heap.clone<Map>(ref.u), ref.type});
		if(is_ostream(ref)) core.stack.push(Value{core.heap.clone<OStream>(ref.u), ref.type});
		if(is_istream(ref)) core.stack.push(Value{core.heap.clone<IStream>(ref.u), ref.type});
		if(is_rng(ref)) core.stack.push(Value{core.heap.clone<RandomEngine>(ref.u), ref.type});
		else throw except::invalid_argument("Cannot clone");
	}
}