#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "convert.hxx"
#include <sstream>
#include <stack>



namespace ltn::vm {
	void LtnVM::jump() {
		const auto addr = this->fetch_uint(); 
		this->pc = addr;
	}



	void LtnVM::call() {
		const auto addr = this->fetch_uint(); 
		this->stack.push_frame(this->pc);
		this->pc = addr;
	}



	void LtnVM::reTurn() {
		this->pc = this->stack.pop_frame();
	}



	void LtnVM::iF() {
		const auto value = this->reg.pop();
		const auto elseAddr = this->fetch_uint();
		if(!convert::to_bool(value)) {
			this->pc = elseAddr;
		}
	}



	void LtnVM::parameters() {
		const auto count = this->fetch_byte();
		auto [begin, end] = this->reg.peek(count);
		for(auto it = begin; it != end; it++) {
			this->stack.make_var(*it);
		}
		this->reg.remove(count);
	}
}