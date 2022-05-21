#include "LtnVM.hxx"
#include "type_check.hxx"
#include <iostream>
#include <string>

namespace ltn::vm {
	void LtnVM::newi(){
		this->core.reg.push(Value{this->fetch_uint(), Value::Type::INT});
	}


	void LtnVM::newf(){
		this->core.reg.push(Value{this->fetch_uint(), Value::Type::FLOAT});
	}


	void LtnVM::newu(){
		this->core.reg.push(Value{this->fetch_uint(), Value::Type::NVLL});
	}
	

	void LtnVM::newc() {
		const auto chr = this->fetch_byte();
		this->core.reg.push(value::character(chr));
	}
	

	void LtnVM::truE(){
		this->core.reg.push(Value{true, Value::Type::BOOL});
	}


	void LtnVM::falsE(){
		this->core.reg.push(Value{false, Value::Type::BOOL});
	}


	void LtnVM::null() {
		this->core.reg.push(Value{false, Value::Type::NVLL});
	}
}