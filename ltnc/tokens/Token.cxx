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
		tokens.pop();
		while(!tokens.empty()) {
			switch (tokens.front().type) {
				case TT::___EOF___: return;
				// case TT::SEMICOLON: return tokens.pop();
				// case TT::NAMESPACE: return;
				// case TT::FUNCTION:  return;
				// case TT::BUILD_IN:  return;
				// case TT::VAR:       return;
				// case TT::FOR:       return;
				// case TT::WHILE:     return;
				// case TT::IF:        return;
				// case TT::ELSE:      return;
				// case TT::RETURN:    return;
			default: break;
			}
			
			tokens.pop();
		}
	}



	const SourceLocation & location(const Tokens & tokens) {
		const static SourceLocation fallback {0, ""};
		return (tokens.empty()) ? fallback : tokens.front().location;
	}
}

