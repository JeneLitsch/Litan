#pragma once
#include <optional>
#include "Token.hxx"
#include "DebugInfo.hxx"
namespace ltn::c::lex {
	class Lexer {
	public:
		Lexer(std::istream & in, std::size_t & line);
		std::optional<lex::Token> match(Token::Type type);
		std::size_t inLine() const { return line; }
		DebugInfo debug() const { return {line}; }
	private:
		std::optional<Token> token;
		std::istream & in;
		std::size_t & line;
	};
}