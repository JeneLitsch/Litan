#include "Api.hxx"

ltn::vm::ext::Api::Api(Heap & heap, Register & reg, const std::vector<Value> & params) 
	: heap(heap), reg(reg), params(params), return_value(value::null) {
}


void ltn::vm::ext::Api::return_bool(bool value) {
	this->return_value = Value{value};
}

void ltn::vm::ext::Api::return_int(std::int64_t value) {
	this->return_value = Value{value};
}

void ltn::vm::ext::Api::return_float(double value) {
	this->return_value = Value{value};
}

void ltn::vm::ext::Api::return_string(std::string value) {
	this->return_value = Value{
		this->heap.alloc<String>({value}),
		Value::Type::STRING};
}


ltn::vm::ext::Api::~Api() {
	this->reg.push(this->return_value);
}
