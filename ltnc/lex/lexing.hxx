#pragma once
#include <string>
#include <istream>
#include "Token.hxx"

namespace ltnc::lex {
	Token token(std::istream & in, std::size_t & line);
}