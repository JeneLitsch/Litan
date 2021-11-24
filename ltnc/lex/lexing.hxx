#pragma once
#include <string>
#include <istream>
#include "Token.hxx"

namespace ltn::c::lex {
	// Returns next token read from "in"
	Token token(std::istream & in, std::size_t & line);
}