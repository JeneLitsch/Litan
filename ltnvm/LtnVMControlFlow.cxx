#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "cast.hxx"
#include <sstream>

namespace ltn::vm {
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
		if(!cast::to_bool(value, this->heap)) {
			this->pc = elseAddr;
		}
	}
}