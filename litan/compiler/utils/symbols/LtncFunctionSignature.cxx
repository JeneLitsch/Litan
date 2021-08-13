#include "LtncFunctionSignature.hxx"

ltn::c::FunctionSignature::FunctionSignature(
	const TypeId & returnType,
	const std::string & name,
	const std::vector<Param> & params,
	const Namespace & ns)
:	Symbol(name, ns),
	returnType(returnType),
	params(params) {}


std::ostream & ltn::c::operator<<(
	std::ostream & stream,
	const FunctionSignature & fxSignature) {
	stream 
		<< fxSignature.ns
		<< fxSignature.name 
		<< "(";
	for(std::size_t idx = 0; idx < fxSignature.params.size(); idx++) {
		stream 
			<< (idx?", ":"") 
			<< fxSignature.params[idx].typeId;
	}
	stream
		<< ")"
		<< " -> "
		<< fxSignature.returnType;
	return stream;
}