#include "LtnVM.hxx"
#include "type_check.hxx"
#include "convert.hxx"
#include <sstream>
#include <stack>



namespace ltn::vm {
	void LtnVM::jump() {
		const auto addr = this->fetch_uint(); 
		this->core.pc = addr;
	}



	void LtnVM::call() {
		const auto addr = this->fetch_uint(); 
		this->core.stack.push_frame(this->core.pc);
		this->core.pc = addr;
	}



	void LtnVM::reTurn() {
		this->core.pc = this->core.stack.pop_frame();
	}



	void LtnVM::iF() {
		const auto value = this->core.reg.pop();
		const auto elseAddr = this->fetch_uint();
		if(!convert::to_bool(value)) {
			this->core.pc = elseAddr;
		}
	}



	void LtnVM::parameters() {
		const auto count = this->fetch_byte();
		auto [begin, end] = this->core.reg.peek(count);
		for(auto it = begin; it != end; it++) {
			this->core.stack.make_var(*it);
		}
		this->core.reg.remove(count);
	}
}