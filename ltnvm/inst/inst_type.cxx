#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <iostream>


namespace ltn::vm::inst {
	void type_id(VmCore & core) {
		const auto value = core.reg.pop();
		core.reg.push(Value{static_cast<std::int64_t>(value.type)});
	}



	void clone(VmCore & core) {
		const auto ref = core.reg.pop();
		if(is_array(ref)) core.reg.push(Value{core.heap.clone<Array>(ref.u), ref.type});
		if(is_string(ref)) core.reg.push(Value{core.heap.clone<String>(ref.u), ref.type});
		if(is_stack(ref)) core.reg.push(Value{core.heap.clone<Deque>(ref.u), ref.type});
		if(is_queue(ref)) core.reg.push(Value{core.heap.clone<Deque>(ref.u), ref.type});
		if(is_map(ref)) core.reg.push(Value{core.heap.clone<Map>(ref.u), ref.type});
		if(is_ostream(ref)) core.reg.push(Value{core.heap.clone<OStream>(ref.u), ref.type});
		if(is_istream(ref)) core.reg.push(Value{core.heap.clone<IStream>(ref.u), ref.type});
		if(is_rng(ref)) core.reg.push(Value{core.heap.clone<RandomEngine>(ref.u), ref.type});
		else throw except::invalid_argument("Cannot clone");
	}
}