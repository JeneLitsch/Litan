#include "LtnVM.hxx"
#include "TypeCheck.hxx"

namespace ltn::vm {
	void LtnVM::read() {
		const auto addr = this->reg.pop();
		const auto value = this->stack.read(addr.u);
		this->reg.push(value);
	}

	void LtnVM::write() {
		const auto addr = this->reg.pop();
		const auto value = this->reg.pop();
		this->stack.write(addr.u, value);
	}
	void LtnVM::scrap() {
		this->reg.pop();
	}
	void LtnVM::makevar() {
		this->stack.makeVar();
	}
}