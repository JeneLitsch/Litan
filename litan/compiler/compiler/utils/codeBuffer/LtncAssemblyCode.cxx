#include "LtncAssemblyCode.hxx"

ltn::c::AssemblyCode::AssemblyCode(const std::string & string)
	: string(string + "\n") {}

ltn::c::AssemblyCode::AssemblyCode(const std::vector<std::string> & strings) {
	for(const std::string & string : strings) {
		this->string += string + "\n";
	}
}

std::string ltn::c::AssemblyCode::toString() const {
	return this->string;
}
