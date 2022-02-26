#include "External.hxx"

ltn::vm::ext::External::External(std::size_t parameters) 
	: parameters(parameters) {}

std::size_t ltn::vm::ext::External::get_parameters() const {
	return this->parameters;
}
