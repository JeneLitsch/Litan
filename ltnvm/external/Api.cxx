#include "Api.hxx"

ltn::vm::ext::Api::Api(Heap & heap, Register & reg, const std::vector<Value> & params) 
	: heap(heap), reg(reg), params(params), returnVal(value::null) {
}


void ltn::vm::ext::Api::returnBool(bool value) {
	this->returnVal = Value{value};
}

void ltn::vm::ext::Api::returnInt(std::int64_t value) {
	this->returnVal = Value{value};
}

void ltn::vm::ext::Api::returnFloat(double value) {
	this->returnVal = Value{value};
}

void ltn::vm::ext::Api::returnString(std::string value) {
	this->returnVal = Value{this->heap.alloc<String>(value), Value::Type::STRING};
}


ltn::vm::ext::Api::~Api() {
	this->reg.push(this->returnVal);
}
