#pragma once

#include <string>
#include <optional>
#include <iostream>
#include <span>
#include <queue>

#include "stdxx/array.hxx"
#include "stdxx/queue.hxx"
#include "stdxx/oop.hxx"

#include "ltnc/SourceLocation.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/Source.hxx"
#include "ltnc/SourceLocation.hxx"

namespace ltn::c {
	struct Token {
		enum class Type {
			___EOF___,
			
			COLON,
			COLONx2,
			
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
			GLOBAL,
			DECLTYPE,
			STATIC_COPY,
			DYNAMIC_COPY,
			REFLECT,
			
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

	using Tokens = stx::closed_queue<Token>;


	std::optional<Token> match(Token::Type type, Tokens & tokens);
	void sync(Tokens & tokens);
	const SourceLocation & location(const Tokens & tokens);
}