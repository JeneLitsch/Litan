#include "Register.hxx"
#include "Float.hxx"

const std::vector<ltn::vm::Value> & ltn::vm::Register::getContainer() const {
	return this->stack;
}

void ltn::vm::Register::reset() {
	this->stack.clear();
}
