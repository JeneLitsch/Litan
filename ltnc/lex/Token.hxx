#pragma once
#include <string>
namespace ltn::c::lex {
	struct Token {
		enum class Type {
			___EOF___,
			INDENTIFIER, FUNCTION, RETURN, VAR, REF, IF, ELSE, WHILE,
			INTEGER, FLOAT, TRUE, FALSE,
			PAREN_L, PAREN_R, BRACE_L, BRACE_R, BRACKET_L, BRACKET_R,
			ARROW, SEMICOLON, COMMA,
			ASSIGN, PLUS, MINUS, STAR, SLASH, PERCENT,
			EQUAL, UNEQUAL, SMALLER, BIGGER, SMALLER_EQUAL, BIGGER_EQUAL,
			NOT, 
		};
		Type type;
		std::string str;
	};
}