#pragma once
#include <vector>
#include "LtncToken.hxx"
#include "LtncNamespace.hxx"
#include "LtnErrorReporter.hxx"
namespace ltn::c {
	class ParserPackage {
	public:
		ParserPackage(
			ltn::ErrorReporter & error,
			const std::vector<Token> & tokens);
		bool test(TokenType type);
		bool test(const std::vector<TokenType> types);
		bool match(TokenType type);
		bool match(const std::vector<TokenType> types);
		void back();
		void advance();
		bool isAtEnd() const;
		const Token & prev() const;
		const Token & curr() const;
		void resync(const std::vector<TokenType> & tokenTypes);

		Namespace ns;
		ltn::ErrorReporter & error;

		operator const DebugInfo&() const;

	private:
		unsigned current;
		std::vector<Token> tokens;
	};
}