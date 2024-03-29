#pragma once
#include <string>
#include <istream>
#include "ltnc/tokens/Token.hxx"
#include "ltnc/SourceLocation.hxx"
#include "ltnc/source/Source.hxx"

namespace ltn::c {
	Tokens tokenize(const Source & source);
}