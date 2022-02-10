#include "Lexer.hxx"
#include "lexing.hxx"
#include <set>
#include "ltnc/CompilerError.hxx"

namespace ltn::c::lex {
	using TT = Token::Type;
	
	void Lexer::load(std::istream & in, std::string sourcename) {
		SourceLocation loc{1, sourcename};
		ErrorAccu errors;
		while (true) {
			try {
				Token t = lex::token(in, loc);
				this->tokens.push_back(t);
				if(t.type == TT::___EOF___) break;
			}
			catch(const CompilerError & error) {
				errors.push(error);
				in.ignore();
			}
		}
		this->current = this->tokens.begin();
		errors.may_throw();
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
			TT::___EOF___,
			TT::SEMICOLON,
			TT::NAMESPACE,
			TT::FUNCTION,
			TT::ASM,
			TT::VAR,
			TT::FOR,
			TT::WHILE,
			TT::IF,
			TT::ELSE,
			TT::BRACE_R,
		};
		
		if(this->current == this->tokens.end()) {
			std::advance(this->current, -1);
			return;
		}
		// std::cout << this->current->str << std::endl;
		if(this->current->type == TT::___EOF___) return;
		std::advance(this->current, 1);
		while(!stops.contains(this->current->type)) {
			// std::cout << this->current->str << "\n";
			std::advance(this->current, 1);
		}
		this->match(TT::SEMICOLON);
	}
}

