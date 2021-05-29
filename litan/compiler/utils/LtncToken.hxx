#pragma once
#include <string>

namespace ltnc {
	enum class TokenType {
		IDENTIFIER = 0x00, NUMBER_INT, NUMBER_FLT, STRING_LITERAL,
		INT = 0x10, FLT, VOI, FNX, CON,
		ASSIGN = 0x20, CALL, RETURN, ASM,
		SEMICOLON = 0x30, COMMA,
		PRINT = 0x40, IF, ELSE, WHILE, FOR, REPEAT,
		L_BRACE = 0x50, R_BRACE, L_PARAN, R_PARAN,
		PLUS = 0x60, MINUS, STAR, SLASH, MOD,
		EQUAL = 0x70, UNEQUAL, SMALLER, BIGGER, SMALLEREQUAL, BIGGEREQUAL,
		___NONE__,
		___EOF___,

		INCLUDE = 0xf0
	};
	struct Token {
		Token(TokenType type, const std::string & string, unsigned line)
		: type(type), string(string), line(line) {}
		TokenType type;
		std::string string;
		unsigned line;
	};
}