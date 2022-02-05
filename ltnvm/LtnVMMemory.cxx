#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "index.hxx"

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





	void LtnVM::read_x() {
		const auto addr = this->fetchUint();
		const auto value = this->stack.read(addr);
		this->reg.push(value);
	}


	void LtnVM::write_x() {
		const auto addr = this->fetchUint();
		const auto value = this->reg.pop();
		this->stack.write(addr, value);
	}


	void LtnVM::read_0() { this->reg.push(this->stack.read(0)); }
	void LtnVM::read_1() { this->reg.push(this->stack.read(1)); }
	void LtnVM::read_2() { this->reg.push(this->stack.read(2)); }
	void LtnVM::read_3() { this->reg.push(this->stack.read(3)); }

	void LtnVM::write_0() { this->stack.write(0, this->reg.pop()); }
	void LtnVM::write_1() { this->stack.write(1, this->reg.pop()); }
	void LtnVM::write_2() { this->stack.write(2, this->reg.pop()); }
	void LtnVM::write_3() { this->stack.write(3, this->reg.pop()); }
}