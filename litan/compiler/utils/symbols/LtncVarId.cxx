#include "LtncVarId.hxx"

std::ostream & ltn::c::operator<<(std::ostream & stream, const VarId & varId){
	stream << varId.ns << varId.name;
	return stream;
}
