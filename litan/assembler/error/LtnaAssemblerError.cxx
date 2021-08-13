#include "LtnaAssemblerError.hxx"

ltn::a::AssemblerError::AssemblerError(
	const std::string & inst,
	std::uint64_t lineNr) 
:	Error("Invalid instruction " + inst + " in line " + std::to_string(lineNr)),
	inst(inst),
	lineNr(lineNr) {}

ltn::a::AssemblerError::AssemblerError(
	const std::string & msg) 
:	Error(msg),
	inst(""),
	lineNr(0) {}

ltn::a::AssemblerError::AssemblerError(
	const std::string & msg,
	const std::string & inst,
	std::uint64_t lineNr) 
:	Error(msg),
	inst(inst),
	lineNr(lineNr) {}

std::uint64_t ltn::a::AssemblerError::getLineNr() const {
	return this->lineNr;
}