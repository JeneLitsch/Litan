#include "LtnaAssemblerError.hxx"

ltna::AssemblerError::AssemblerError(
	const std::string & inst,
	std::uint64_t lineNr) 
:	Error("Invalid instruction " + inst + " in line " + std::to_string(lineNr)),
	inst(inst),
	lineNr(lineNr) {}

ltna::AssemblerError::AssemblerError(
	const std::string & msg,
	const std::string & inst,
	std::uint64_t lineNr) 
:	Error(msg),
	inst(inst),
	lineNr(lineNr) {}

std::uint64_t ltna::AssemblerError::getLineNr() const {
	return this->lineNr;
}