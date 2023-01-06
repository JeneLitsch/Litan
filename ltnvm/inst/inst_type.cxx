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
		if(isObject(ref)) {
			const auto & newref = core.heap.clone(ref.u);
			core.reg.push(Value{newref, ref.type});
		}
		else throw except::invalid_argument();
	}
}