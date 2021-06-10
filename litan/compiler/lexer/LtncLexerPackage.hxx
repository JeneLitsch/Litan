#pragma once
#include <string>
#include <vector>
#include "LtncToken.hxx"
namespace ltnc {
	// Data container for Lexer
	// Can be passed through lexing tree
	class LexerPackage {
	public:
		LexerPackage(const std::string & code);

		// Returns true if all characters are processed
		bool isAtEnd() const;
		// Matches character and continues
		bool match(char chr);
		// Matches letter and continues
		bool matchAlpha();
		// Matches digit and continues
		bool matchDigit();

		// Increment line counter;
		void newLine();
		// Set start to current
		void sync();
		// Goto to next character
		void next();

		// Returns string between start and current
		std::string makeLexeme() const;
		
		// Create token
		void newToken(TokenType type);
		// Create token with custom string
		void newToken(TokenType type, const std::string & lexeme);
		// Add token
		void addToken(Token token);
		
		const std::vector<Token> getTokens() const;
		// Throws error with extra infos
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