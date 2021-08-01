#include "Ltna.hxx"

std::vector<std::uint64_t> ltna::Ltna::assemble(const std::string & assembly) {
	std::vector<ltna::TokenPackage> tokenPkg;
	tokenPkg = this->assemblerParser.parse(assembly);
	tokenPkg = this->pseudoAssembler.process(tokenPkg);
	return this->assembler.assemble(tokenPkg);
}

void ltna::Ltna::registerAlias(const std::string & alias, ltn::Slot slot, std::uint8_t funct) {
	this->pseudoAssembler.registerAlias(alias, slot, funct);
}
