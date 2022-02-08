#include "Lexer.hxx"
#include "lexing.hxx"
#include <set>

namespace ltn::c::lex {
	using TT = Token::Type;
	
	Lexer::Lexer(std::istream & in, std::string sourcename)
		:	in(in) {
		SourceLocation loc{1, sourcename};
		Token t = lex::token(in, loc);
		while (t.type != TT::___EOF___) {
			this->tokens.push_back(t);
			t = lex::token(in, loc);
		}
		this->tokens.push_back(t);
		this->current = this->tokens.begin();
	}


	std::optional<Token> Lexer::match(Token::Type type) {
		if(this->current->type == type) {
			Token t = *this->current; 
			std::advance(this->current, 1);
			return t;
		}
		else {
			return {};
		}
	}


	void Lexer::sync() {
		const static std::set<TT> stops {
			TT::NAMESPACE,
			TT::FUNCTION,
			TT::ASM,
			TT::___EOF___,
		};

		while(!stops.contains(this->current->type)) {
			std::advance(this->current, 1);
		}
	}
}

