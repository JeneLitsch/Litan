#include "Register.hxx"

const std::vector<ltn::vm::Value> & ltn::vm::Register::get_container() const {
	return this->stack;
}

void ltn::vm::Register::reset() {
	this->stack.clear();
}

std::size_t ltn::vm::Register::size() const {
	return this->stack.size();
}

