#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>


namespace ltn::vm {
	void LtnVM::typeId() {
		const auto value = this->reg.pop();
		this->reg.push(Value{static_cast<std::int64_t>(value.type)});
	}
}