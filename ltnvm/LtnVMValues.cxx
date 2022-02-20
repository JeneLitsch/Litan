#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>
#include <string>

namespace ltn::vm {
	void LtnVM::newi(){
		this->reg.push(Value{this->fetchUint(), Value::Type::INT});
	}


	void LtnVM::newf(){
		this->reg.push(Value{this->fetchUint(), Value::Type::FLOAT});
	}


	void LtnVM::newu(){
		this->reg.push(Value{this->fetchUint(), Value::Type::NVLL});
	}
	

	void LtnVM::newc() {
		const auto chr = this->fetchByte();
		this->reg.push(value::character(chr));
	}
	

	void LtnVM::truE(){
		this->reg.push(Value{true, Value::Type::BOOL});
	}


	void LtnVM::falsE(){
		this->reg.push(Value{false, Value::Type::BOOL});
	}


	void LtnVM::null() {
		this->reg.push(Value{false, Value::Type::NVLL});
	}
}