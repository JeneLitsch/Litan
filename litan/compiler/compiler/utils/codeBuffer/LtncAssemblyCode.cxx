#include "LtncAssemblyCode.hxx"

ltnc::AssemblyCode::AssemblyCode(const std::string & string)
	: string(string + "\n") {}

ltnc::AssemblyCode::AssemblyCode(const std::vector<std::string> & strings) {
	for(const std::string & string : strings) {
		this->string += string + "\n";
	}
}

std::string ltnc::AssemblyCode::toString() const {
	return this->string;
}
