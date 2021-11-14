#pragma once
#include <string>
#include <istream>
#include "Token.hxx"

namespace ltn::c::lex {
	Token token(std::istream & in, std::size_t & line);
}