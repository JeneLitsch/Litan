#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;

		std::unique_ptr<ast::Assignable> unaryA(
			lex::Lexer & lexer,
			std::unique_ptr<ast::Assignable> l) {
			
			if(auto index = parse::index(lexer)) {
				auto full = std::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					index->debugInfo);
				return unaryA(lexer, std::move(full));
			}
			return l;
		}
	}
	

	std::unique_ptr<ast::Assignable> assignable(lex::Lexer & lexer) {
		if(auto name = lexer.match(TT::INDENTIFIER)) {
			auto expr = std::make_unique<ast::Var>(name->str, lexer.debug());
			return unaryA(lexer, std::move(expr));
		}
		return nullptr;
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