#include "LtnVM.hxx"
#include "TypeCheck.hxx"



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
	void LtnVM::addr(){
		this->reg.push(Value{this->fetchUint(), Value::Type::ADDR});
	}
	void LtnVM::truE(){
		this->reg.push(Value{true, Value::Type::BOOL});
	}
	void LtnVM::falsE(){
		this->reg.push(Value{false, Value::Type::BOOL});
	}
	void LtnVM::newarr(){
		throw std::runtime_error {"No heap allocation implented"};
	}
	void LtnVM::null() {
		this->reg.push(Value{false, Value::Type::NVLL});
	}
}