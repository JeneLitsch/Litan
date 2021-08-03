#include "LtncTokenDebugInfo.hxx"

ltnc::TokenDebugInfo::TokenDebugInfo(
	unsigned lineNr,
	unsigned column,
	const std::string & lexeme)
:	lineNr(lineNr),
	column(column),
	lexeme(lexeme) {}

ltnc::TokenDebugInfo::TokenDebugInfo()
:	lineNr(0),
	column(0),
	lexeme("") {}

