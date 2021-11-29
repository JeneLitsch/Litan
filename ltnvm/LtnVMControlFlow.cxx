#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <sstream>

namespace ltn::vm {


	bool isTruthy(const Value & value) {
		if(isBool(value)) return value.b;
		if(isInt(value)) return value.i;
		if(isFloat(value)) return value.f == 0.0;
		throw std::runtime_error{"Cannot convert to bool"};
	}

	void LtnVM::jump() {
		const auto addr = this->fetchUint(); 
		this->pc = addr;
	}
	void LtnVM::call() {
		const auto addr = this->fetchUint(); 
		this->stack.pushFrame(this->pc);
		this->pc = addr;
	}
	void LtnVM::reTurn() {
		this->pc = this->stack.popFrame();
	}
	void LtnVM::iF() {
		const auto value = this->reg.pop();
		const auto elseAddr = this->fetchUint();
		if(!isTruthy(value)) {
			this->pc = elseAddr;
		}
	}
	void LtnVM::error() {
		throw std::runtime_error{"An error was thrown during runtime"};
	}

}