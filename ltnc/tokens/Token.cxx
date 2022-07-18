#include "Token.hxx"
#include <set>
#include <sstream>
#include "ltnc/CompilerError.hxx"



namespace ltn::c {
	using TT = Token::Type;

	const Token Token::end = Token{Token::Type::___EOF___, "___EOF___", SourceLocation{}};



	std::optional<Token> match(Token::Type type, Tokens & tokens) {
		if(tokens.empty()) return std::nullopt;
		const Token t = tokens.front(); 
		if(t.type != type) return std::nullopt;
		tokens.pop();
		return t;
	}



	void sync(Tokens & tokens) {
		const static std::set<TT> stops {
			TT::___EOF___,
			TT::SEMICOLON,
			TT::NAMESPACE,
			TT::FUNCTION,
			TT::BUILD_IN,
			TT::VAR,
			TT::FOR,
			TT::WHILE,
			TT::IF,
			TT::ELSE,
			TT::BRACE_R,
		};
		
		// if(tokens.empty()) {
		// 	tokens.unpop();
		// 	return;
		// }
		// std::cout << this->current->str << std::endl;
		if(tokens.front().type == TT::___EOF___) return;
		tokens.pop();
		while(!stops.contains(tokens.front().type)) {
			// std::cout << this->current->str << "\n";
			tokens.pop();
		}
		match(TT::SEMICOLON, tokens);
	}



	const SourceLocation & location(const Tokens & tokens) {
		const static SourceLocation fallback {0, ""};
		return (tokens.empty()) ? fallback : tokens.front().location;
	}
}

