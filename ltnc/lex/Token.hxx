#pragma once
#include <string>
#include "ltnc/SourceLocation.hxx"
namespace ltn::c::lex {
	struct Token {
		enum class Type {
			___EOF___, COLON, COLONx2,
			
			INDENTIFIER,
			FUNCTION,
			LAMBDA,
			VAR,
			IF,
			ELSE,
			WHILE,
			RETURN,
			FOR,
			NAMESPACE,
			EXCEPT,
			THROW,
			IIFE,
			BUILD_IN,
			ENUM,
			DEFINE,
			PRESET,
			SWITCH,
			CHOOSE,
			CASE,
			DEFAULT,
			
			INTEGER,
			INTEGER_HEX,
			INTEGER_BIN,
			FLOAT,
			TRUE,
			FALSE,
			STRING,
			CHAR,
			NVLL,
			
			PAREN_L,
			PAREN_R,
			BRACE_L,
			BRACE_R,
			BRACKET_L,
			BRACKET_R,
			
			SEMICOLON,
			COMMA,
			AMPERSAND,
			UNDERSCORE,
			DOT,
			XMARK,
			QMARK,
			ASSIGN,
			AT,
			
			PLUS,
			MINUS,
			STAR,
			SLASH,
			PERCENT,
			STARx2,
			SHIFT_L,
			SHIFT_R,
			BIT_OR,
			BIT_XOR,
			
			ASSIGN_ADD,
			ASSIGN_SUB,
			ASSIGN_MLT,
			ASSIGN_DIV,
			ASSIGN_MOD,
			ASSIGN_POW,
			ASSIGN_SHIFT_L,
			ASSIGN_SHIFT_R,
			ASSIGN_BIT_AND,
			ASSIGN_BIT_OR,
			ASSIGN_BIT_XOR,
			
			AND, OR,
			
			EQUAL,
			UNEQUAL,
			SMALLER,
			BIGGER,
			SMALLER_EQUAL,
			BIGGER_EQUAL,
			SPACE_SHIP,
			TILDE,

			RARROW,
			DRARROW,
		};
		
		Type type;
		std::string str;
		SourceLocation location;
		static const Token end;
	};
}