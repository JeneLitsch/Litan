#pragma once
#include <string>
#include <istream>
#include "litan_compiler/tokens/Token.hxx"
#include "litan_compiler/SourceLocation.hxx"
#include "litan_compiler/source/Source.hxx"

namespace ltn::c {
	Tokens tokenize(const Source & source);
}