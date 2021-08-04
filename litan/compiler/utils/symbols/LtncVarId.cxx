#include "LtncVarId.hxx"

std::ostream & ltnc::operator<<(std::ostream & stream, const VarId & varId){
	stream << varId.ns << varId.name;
	return stream;
}
