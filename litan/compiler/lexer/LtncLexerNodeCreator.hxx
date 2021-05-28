#pragma once
#include "LtncLexerNode.hxx"
namespace ltnc {
	class LexerNodeCreator {
	public:
		static LexerNode chr(char chr, std::vector<LexerNode> nodes);
		static LexerNode chr(char chr, TokenType type);
		static LexerNode chr(char chr, TokenType type, std::vector<LexerNode> nodes);

		static LexerNode connector(std::vector<LexerNode> nodes);

		static LexerNode ignore(char chr);
		static LexerNode ignoreLine();

		static LexerNode newLine();

		static LexerNode numliteral();
		static LexerNode identifier();
	};
}