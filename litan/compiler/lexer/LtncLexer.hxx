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
		std::vector<Token> tokenize(const std::string & str);
	private:
		void process(LexerPackage & lexPkg,	LexerNode & tree);
	};
}