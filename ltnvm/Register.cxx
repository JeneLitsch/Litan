#include "Register.hxx"
#include "Float.hxx"

std::uint64_t ltn::vm::Register::popU() {
	const std::uint64_t value = this->stack.back();
	this->stack.pop_back();
	return value;
}
std::int64_t ltn::vm::Register::popI() {
	return static_cast<std::int64_t>(this->popU());
}
double ltn::vm::Register::popF() {
	return toFloat(this->popU());
}

void ltn::vm::Register::pushU(std::uint64_t value) {
	this->stack.push_back(value);
}
void ltn::vm::Register::pushI(std::int64_t value) {
	this->stack.push_back(static_cast<std::uint64_t>(value));
}
void ltn::vm::Register::pushF(double value) {
	this->stack.push_back(toUint(value));
}
