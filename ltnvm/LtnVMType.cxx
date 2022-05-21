#include "LtnVM.hxx"
#include "type_check.hxx"
#include <iostream>


namespace ltn::vm {
	void LtnVM::type_id() {
		const auto value = this->core.reg.pop();
		this->core.reg.push(Value{static_cast<std::int64_t>(value.type)});
	}

	void LtnVM::clone() {
		const auto ref = this->core.reg.pop();
		if(isObject(ref)) {
			const auto & newref = this->core.heap.clone(ref.u);
			this->core.reg.push(Value{newref, ref.type});
		}
		else throw except::invalid_argument();
	}
}