#include "parsing.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		
		std::unique_ptr<ast::Expression> conditionals(lex::Lexer & lexer) {
			auto expr = logical_and(lexer);
			if(lexer.match(TT::QMARK)) {
				if(lexer.match(TT::QMARK)) {
					auto else_expr = expression(lexer);
					return std::make_unique<ast::Nullco>(
						lexer.location(),
						std::move(expr),
						std::move(else_expr));
				}

				if(lexer.match(TT::COLON)) {
					auto else_expr = expression(lexer);
					return std::make_unique<ast::Elvis>(
						lexer.location(),
						std::move(expr),
						std::move(else_expr));
				}
				
				auto if_expr = expression(lexer);
				if(!lexer.match(TT::COLON)) {

				}
				auto else_expr = expression(lexer);
				return std::make_unique<ast::Ternary>(
					lexer.location(),
					std::move(expr),
					std::move(if_expr),
					std::move(else_expr));
			}
			return expr;
		}


	}


	// generic expression
	std::unique_ptr<ast::Expression> expression(lex::Lexer & lexer) {
		return conditionals(lexer);
	}
}

