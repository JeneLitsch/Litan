#pragma once
#include <vector>
#include "LtncToken.hxx"
#include "LtncNamespace.hxx"
namespace ltnc {
	class ParserPackage {
	public:
		ParserPackage(const std::vector<Token> & tokens);
		bool match(TokenType type);
		bool match(const std::vector<TokenType> types);
		void back();
		bool isAtEnd() const;
		const Token & prev() const;
		const Token & curr() const;

		std::nullptr_t error(const std::string & msg);
		Namespace ns;

	private:
		unsigned current;
		std::vector<Token> tokens;
	};
}