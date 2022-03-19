#pragma once
#include <optional>
#include <iostream>
#include <span>
#include <vector>
#include "Token.hxx"
#include "ltnc_core/SourceLocation.hxx"
#include "ltnc_core/Reporter.hxx"
namespace ltn::c::lex {

	class Lexer {
	public:
		Lexer(std::istream & in, std::string sourcename, Reporter & reporter);
		std::optional<lex::Token> match(Token::Type type);
		bool check(Token::Type type);
		void sync();
		
		std::size_t inLine() const {
			return this->location().line;
		}
		
		const SourceLocation & location() const {
			if(this->current == tokens.end()) {
				return this->tokens.back().location; 
			}
			return current->location;
		}

	private:
		std::vector<Token> tokens;
		std::vector<Token>::iterator current;
	};
}