#include "Lexer.hxx"
#include "lexing.hxx"

namespace ltn::c::lex {
	using TT = Token::Type;
	Lexer::Lexer(std::istream & in, std::string sourcename)
		:	in(in) {
		this->loc = SourceLocation{1, sourcename};
		Token t = lex::token(in, this->loc);
		while (t.type != TT::___EOF___) {
			this->tokens.push_back(t);
			t = lex::token(in, loc);
		}
		this->tokens.push_back(Token::end);
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
		auto stops = std::array{
			TT::NAMESPACE,
			TT::FUNCTION,
			TT::ASM,
			TT::___EOF___,
		};
		while(true) {
			for(const auto tt : stops) {
				if(this->current->type == tt) return;
			}
			std::advance(this->current, 1);
		}
	}
}

