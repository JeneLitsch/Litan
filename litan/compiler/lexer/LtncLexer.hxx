#pragma once
#include <vector>
#include <map>
#include "LtncToken.hxx"
#include "LtncLexerPackage.hxx"
#include "LtncLexerNodeCreator.hxx"
#include "LtncLexerNode.hxx"
namespace ltnc {
	class Lexer {
	public:
		Lexer();
		std::vector<Token> tokenize(
			const std::string & source,
			const std::string & sourceName);
	private:
		void process(LexerPackage & lexPkg,	LexerNode & tree);
	};
}