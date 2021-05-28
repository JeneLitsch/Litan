#include "Ltna.hxx"

std::vector<std::uint64_t> ltna::Ltna::assemble(const std::string & assembly) const {
	ltn::Assembler asmr;
	ltn::AssemblerParser asmParser;
	std::vector<ltn::TokenPackage> tokenPkg = asmParser.parse(assembly);
	return asmr.assemble(tokenPkg);
}
