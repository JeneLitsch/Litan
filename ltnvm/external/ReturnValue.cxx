#include "ReturnValue.hxx"

namespace ltn::vm::ext {
	ReturnValue::ReturnValue(Heap & heap, Register & reg) 
		: heap(heap)
		, reg(reg)
		, returned_value(value::null) {}


	ReturnValue::~ReturnValue() {
		this->reg.push(this->returned_value);
	}
}

