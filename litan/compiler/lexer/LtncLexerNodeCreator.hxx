#pragma once
#include "LtncLexerNode.hxx"
namespace ltnc {
	// creates a variaty of lexing nodes
	class LexerNodeCreator {
	public:
		// matches single character but is not allowed as an result
		static LexerNode chr(char chr, std::vector<LexerNode> nodes);
		// matches single character 
		static LexerNode chr(char chr, TokenType type);
		// matches single character and continues with child nodes
		static LexerNode chr(char chr, TokenType type, std::vector<LexerNode> nodes);

		// can contain multiple other nodes
		static LexerNode connector(std::vector<LexerNode> nodes);

		// skip one character
		static LexerNode ignore(char chr);
		// skip the rest of the line
		static LexerNode ignoreLine();

		// ignores newline but increments line counter
		static LexerNode newLine();

		// matchs unsigned int or float number
		static LexerNode numliteral();
		// matches a valid indentifier
		static LexerNode identifier();
		// matches string between double quotes
		static LexerNode string();
	};
}