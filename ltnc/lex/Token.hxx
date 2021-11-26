#pragma once
#include <string>
#include "DebugInfo.hxx"
namespace ltn::c::lex {
	struct Token {
		enum class Type {
			___EOF___, COLONx2,
			INDENTIFIER, FUNCTION, VAR, IF, ELSE, WHILE, RETURN, NEW, FOR, ASM, NAMESPACE,
			INTEGER, FLOAT, TRUE, FALSE, STRING,
			PAREN_L, PAREN_R, BRACE_L, BRACE_R, BRACKET_L, BRACKET_R,
			SEMICOLON, COMMA, AMPERSAND, UNDERSCORE,
			ASSIGN, PLUS, MINUS, STAR, SLASH, PERCENT,
			EQUAL, UNEQUAL, SMALLER, BIGGER, SMALLER_EQUAL, BIGGER_EQUAL,
			NOT,
			SHIFT_L, SHIFT_R,
		};
		Type type;
		std::string str;
	};
}