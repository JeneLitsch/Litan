#include "LtncDebugInfo.hxx"

ltn::c::DebugInfo::DebugInfo(
	unsigned lineNr,
	unsigned column,
	const std::string & lexeme,
	const std::string & sourceName)
:	lineNr(lineNr),
	column(column),
	lexeme(lexeme),
	sourceName(sourceName) {}

ltn::c::DebugInfo::DebugInfo()
:	lineNr(0),
	column(0),
	lexeme("") {}

ltn::c::DebugInfo ltn::c::DebugInfo::withFunction(
	const FunctionSignature & inFunction) const{
	DebugInfo debugInfo = *this;
	debugInfo.inFunction = inFunction;
	return debugInfo; 
}
