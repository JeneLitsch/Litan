#include "LtnaUnknownInstruction.hxx"

ltn::a::UnknownInstruction::UnknownInstruction(
	const std::string & inst,
	std::uint64_t lineNr)
: 	AssemblerError("Cannot translate unknown instruction \"" + inst + "\"",
		inst, lineNr) {}