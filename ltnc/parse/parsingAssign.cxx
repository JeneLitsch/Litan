#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;

		std::unique_ptr<ast::Assignable> assignable(lex::Lexer & lexer) {
			if(auto name = lexer.match(TT::INDENTIFIER)) {
				return std::make_unique<ast::Var>(name->str, lexer.debug());
			}
			return nullptr;
		}
	}
	

	std::unique_ptr<ast::Expression> assign(lex::Lexer & lexer) {
		if(auto l = assignable(lexer)) {
			if(auto r = assignR(lexer)) {
				return std::make_unique<ast::Assign>(std::move(l), std::move(r), lexer.debug());
			}
			return l;
		}
		return parse::expression(lexer); 
	}

	std::unique_ptr<ast::Expression> assignR(lex::Lexer & lexer) {
		if(lexer.match(TT::ASSIGN)) {
			return expression(lexer);
		}
		return nullptr;
	}

}