#pragma once
#include <string>
#include <vector>
#include "LtncToken.hxx"
namespace ltnc {
	class LexerPackage {
	public:
		LexerPackage(const std::string & code);

		bool isAtEnd() const;
		bool match(char chr);
		bool matchAlpha();
		bool matchDigit();

		void newLine();
		void sync();
		void next();

		std::string makeLexeme() const;
		void newToken(TokenType type);
		void newToken(TokenType type, const std::string & lexeme);
		void addToken(Token token);
		const std::vector<Token> getTokens() const;
		std::nullptr_t error(const std::string & msg);

	private:
		unsigned getLine() const;
		unsigned start = 0;
		unsigned current = 0;
		unsigned line = 0;
		std::string string;
		std::vector<Token> tokens;
	};
}