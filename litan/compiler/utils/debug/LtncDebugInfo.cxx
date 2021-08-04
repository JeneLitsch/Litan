#include "LtncDebugInfo.hxx"

ltnc::DebugInfo::DebugInfo(
	unsigned lineNr,
	unsigned column,
	const std::string & lexeme,
	const std::string & sourceName)
:	lineNr(lineNr),
	column(column),
	lexeme(lexeme),
	sourceName(sourceName) {}

ltnc::DebugInfo::DebugInfo()
:	lineNr(0),
	column(0),
	lexeme("") {}

ltnc::DebugInfo ltnc::DebugInfo::withFunction(
	const FunctionSignature & inFunction) const{
	DebugInfo debugInfo = *this;
	debugInfo.inFunction = inFunction;
	return debugInfo; 
}
