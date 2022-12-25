#pragma once
#include <string>
#include <istream>
#include "ltnc/tokens/Token.hxx"
#include "ltnc/SourceLocation.hxx"
#include "ltnc/source/Source.hxx"
#include "ltnc/Reporter.hxx"

namespace ltn::c {
	Tokens lex(
		const std::vector<Source> & sources,
		Reporter & reporter);
}