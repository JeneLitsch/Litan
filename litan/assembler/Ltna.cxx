#include "Ltna.hxx"

std::vector<std::uint64_t> ltna::Ltna::assemble(const std::string & assembly) {
	std::vector<ltna::TokenPackage> tokenPkg = this->asmParser.parse(assembly);
	return this->asmr.assemble(tokenPkg);
}

void ltna::Ltna::registerAlias(const std::string & alias, ltn::Slot slot, std::uint8_t funct) {
	this->asmr.registerAlias(alias, slot, funct);
}
