#pragma once
#include <string>
#include <istream>
#include "Token.hxx"
#include "ltnc_core/SourceLocation.hxx"
namespace ltn::c::lex {
	// Returns next token read from "in"
	Token token(std::istream & in, SourceLocation & location);
}