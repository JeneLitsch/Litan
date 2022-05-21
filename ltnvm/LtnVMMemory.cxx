#include "LtnVM.hxx"
#include "type_check.hxx"
#include "index.hxx"

namespace ltn::vm {
	void LtnVM::read() {
		const auto addr = this->core.reg.pop();
		const auto value = this->core.stack.read(addr.u);
		this->core.reg.push(value);
	}


	void LtnVM::write() {
		const auto addr = this->core.reg.pop();
		const auto value = this->core.reg.pop();
		this->core.stack.write(addr.u, value);
	}


	void LtnVM::scrap() {
		this->core.reg.pop();
	}

	void LtnVM::duplicate() {
		this->core.reg.push(this->core.reg.peek());
	}


	void LtnVM::makevar() {
		this->core.stack.make_var();
	}


	void LtnVM::read_x() {
		const auto addr = this->fetch_uint();
		const auto value = this->core.stack.read(addr);
		this->core.reg.push(value);
	}


	void LtnVM::write_x() {
		const auto addr = this->fetch_uint();
		const auto value = this->core.reg.pop();
		this->core.stack.write(addr, value);
	}


	void LtnVM::swap() {
		const auto a = this->core.reg.pop();
		const auto b = this->core.reg.pop();
		this->core.reg.push(a);
		this->core.reg.push(b);
	}


	void LtnVM::read_0() { this->core.reg.push(this->core.stack.read(0)); }
	void LtnVM::read_1() { this->core.reg.push(this->core.stack.read(1)); }
	void LtnVM::read_2() { this->core.reg.push(this->core.stack.read(2)); }
	void LtnVM::read_3() { this->core.reg.push(this->core.stack.read(3)); }

	void LtnVM::write_0() { this->core.stack.write(0, this->core.reg.pop()); }
	void LtnVM::write_1() { this->core.stack.write(1, this->core.reg.pop()); }
	void LtnVM::write_2() { this->core.stack.write(2, this->core.reg.pop()); }
	void LtnVM::write_3() { this->core.stack.write(3, this->core.reg.pop()); }
}