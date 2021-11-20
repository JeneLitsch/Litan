#include "LtnVM.hxx"
#include "TypeCheck.hxx"

namespace ltn::vm {
	bool isTruthy(const Value & value) {
		if(isBool(value)) return value.b;
		if(isInt(value)) return value.i;
		throw std::runtime_error{"Cannot convert to bool"};
	}

	void LtnVM::jump() {
		const auto addr = this->fetchUint(); 
		this->out.get() << "Jump: " << std::hex << addr << "\n" << std::dec;
		this->pc = addr;
	}
	void LtnVM::call() {
		const auto addr = this->fetchUint(); 
		this->out.get() << "Call: " << std::hex << addr << "\n" << std::dec;
		this->stack.pushFrame(this->pc);
		this->pc = addr;
	}
	void LtnVM::reTurn() {
		this->pc = this->stack.popFrame();
	}
	void LtnVM::iF() {
		const auto value = this->reg.pop();
		if(!isTruthy(value)) {
			pc++;
		}
	}
	void LtnVM::error() {
		throw std::runtime_error{"An error was thrown during runtime"};
	}
}