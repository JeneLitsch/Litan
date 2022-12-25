#include "Api.hxx"

ltn::vm::ext::Api::Api(Heap & heap, Register & reg, const std::vector<Value> & params) 
	: heap(heap), reg(reg), params(params), returned_value(value::null) {
}


void ltn::vm::ext::Api::return_value(bool value) {
	this->returned_value = Value{value};
}

void ltn::vm::ext::Api::return_value(std::int64_t value) {
	this->returned_value = Value{value};
}

void ltn::vm::ext::Api::return_value(stx::float64_t value) {
	this->returned_value = Value{value};
}

void ltn::vm::ext::Api::return_value(std::string value) {
	this->returned_value = Value{
		this->heap.alloc<String>({value}),
		Value::Type::STRING};
}


ltn::vm::ext::Api::~Api() {
	this->reg.push(this->returned_value);
}
