#pragma once
#include <optional>
#include <iostream>
#include <span>
#include "stdxx/array.hxx"
#include "stdxx/oop.hxx"
#include "Token.hxx"
#include "ltnc/SourceLocation.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/Source.hxx"

namespace ltn::c {

	class Tokens : stx::non_moveable, stx::non_copyable {
	public:
		Tokens(std::vector<lex::Token> tokens);
		std::optional<lex::Token> match(lex::Token::Type type);
		bool check(lex::Token::Type type);
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
		std::vector<lex::Token> tokens;
		std::vector<lex::Token>::iterator current;
	};

	Tokens lex_sources(std::vector<Source> sources, Reporter & reporter);

	std::optional<lex::Token> match(lex::Token::Type type, Tokens & tokens);	
}