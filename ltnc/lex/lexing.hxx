#pragma once
#include <string>
#include <istream>
#include "ltnc/tokens/Token.hxx"
#include "ltnc/SourceLocation.hxx"
#include "ltnc/source/Source.hxx"
#include "ltnc/Reporter.hxx"

namespace ltn::c::lex {
	// Returns next token read from "in"
	Token token(std::istream & in, SourceLocation & location);
	Tokens lex_sources(
		const std::vector<std::unique_ptr<Source>> & sources,
 		Reporter & reporter
	);
}

namespace ltn::c {
	Tokens tokenize(
		const std::vector<Source> & sources,
		Reporter & reporter);
}