#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "convert.hxx"
#include <sstream>
#include <stack>



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
		if(!convert::to_bool(value)) {
			this->pc = elseAddr;
		}
	}



	void LtnVM::parameters() {
		const auto count = this->fetchByte();
		auto [begin, end] = this->reg.peek(count);
		for(auto it = begin; it != end; it++) {
			this->stack.makeVar(*it);
		}
		this->reg.remove(count);
	}
}