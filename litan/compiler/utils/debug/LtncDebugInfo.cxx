#include "LtncDebugInfo.hxx"

ltnc::DebugInfo::DebugInfo(
	unsigned lineNr,
	unsigned column,
	const std::string & lexeme)
:	lineNr(lineNr),
	column(column),
	lexeme(lexeme) {}