#pragma once
#include <string>
#include "ltnc/SourceLocation.hxx"
namespace ltn::c::lex {
	struct Token {
		enum class Type {
			___EOF___, COLONx2,
			INDENTIFIER, FUNCTION, LAMBDA, VAR, CONST, IF, ELSE, WHILE, RETURN, FOR, ASM, NAMESPACE, EXCEPT, THROW,
			INTEGER, INTEGER_HEX, INTEGER_BIN, FLOAT, TRUE, FALSE, STRING, CHAR, NVLL,
			PAREN_L, PAREN_R, BRACE_L, BRACE_R, BRACKET_L, BRACKET_R,
			SEMICOLON, COMMA, AMPERSAND, UNDERSCORE,
			ASSIGN, PLUS, MINUS, STAR, SLASH, PERCENT,
			EQUAL, UNEQUAL, SMALLER, BIGGER, SMALLER_EQUAL, BIGGER_EQUAL,
			NOT,
			SHIFT_L, SHIFT_R, AND, OR,
			ASSIGN_ADD, ASSIGN_SUB, ASSIGN_MLT, ASSIGN_DIV, ASSIGN_MOD, 
			DOT,
		};
		Type type;
		std::string str;
		SourceLocation location;
		static const Token end;
	};
}