#include "Ltna.hxx"

std::vector<std::uint64_t> ltn::a::Ltna::assemble(const std::string & assembly) {
	std::vector<ltn::a::TokenPackage> tokenPkg;
	tokenPkg = this->assemblerParser.parse(assembly);
	tokenPkg = this->pseudoAssembler.process(tokenPkg);
	return this->assembler.assemble(tokenPkg);
}

void ltn::a::Ltna::registerAlias(const std::string & alias, ltn::Slot slot, std::uint8_t funct) {
	this->pseudoAssembler.registerAlias(alias, slot, funct);
}
