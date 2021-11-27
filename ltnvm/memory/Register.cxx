#include "Register.hxx"
#include "Float.hxx"

ltn::vm::Value ltn::vm::Register::pop() {
	const auto value = this->stack.back();
	this->stack.pop_back();
	return value;
}

void ltn::vm::Register::push(ltn::vm::Value value) {
	this->stack.push_back(value);
}

ltn::vm::Value ltn::vm::Register::peek() {
	return this->stack.back();
}

const std::vector<ltn::vm::Value> & ltn::vm::Register::getContainer() const {
	return this->stack;
}

void ltn::vm::Register::reset() {
	this->stack.clear();
}