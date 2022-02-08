#pragma once
#include <optional>
#include <iostream>
#include <span>
#include <vector>
#include "Token.hxx"
#include "ltnc/SourceLocation.hxx"
namespace ltn::c::lex {

	class Lexer {
	public:
		Lexer(std::istream & in, std::string sourcename);
		std::optional<lex::Token> match(Token::Type type);
		void sync();
		std::size_t inLine() const { return loc.line; }
		const SourceLocation & location() const { return loc; }
	private:
		std::vector<Token> tokens;
		std::vector<Token>::iterator current;
		std::istream & in;
		SourceLocation loc;
	};
}