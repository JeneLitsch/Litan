#pragma once
#include <string>
#include "DebugInfo.hxx"
namespace ltn::c::lex {
	struct Token {
		enum class Type {
			___EOF___,
			INDENTIFIER, FUNCTION, VAR, IF, ELSE, WHILE, RETURN, NEW,
			INTEGER, FLOAT, TRUE, FALSE,
			PAREN_L, PAREN_R, BRACE_L, BRACE_R, BRACKET_L, BRACKET_R,
			ARROW, SEMICOLON, COMMA,
			ASSIGN, PLUS, MINUS, STAR, SLASH, PERCENT,
			EQUAL, UNEQUAL, SMALLER, BIGGER, SMALLER_EQUAL, BIGGER_EQUAL,
			NOT,
			PIPE, 
		};
		Type type;
		std::string str;
	};
}