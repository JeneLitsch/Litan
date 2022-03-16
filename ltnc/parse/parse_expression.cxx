#include "parse.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;


		ast::expr_ptr nullco(lex::Lexer & lexer, ast::expr_ptr l) {
			auto else_expr = expression(lexer);
			return std::make_unique<ast::Nullco>(
				lexer.location(),
				std::move(l),
				std::move(else_expr));
		}



		ast::expr_ptr elvis(lex::Lexer & lexer, ast::expr_ptr l) {
			auto else_expr = expression(lexer);
			return std::make_unique<ast::Elvis>(
				lexer.location(),
				std::move(l),
				std::move(else_expr));
		}


		ast::expr_ptr ternary(lex::Lexer & lexer, ast::expr_ptr l) {
			auto c = expression(lexer);
			if(!lexer.match(TT::COLON)) {
				throw CompilerError{"Expected :", lexer.location()};
			}
			auto r = expression(lexer);
			return std::make_unique<ast::Ternary>(
				lexer.location(),
				std::move(l),
				std::move(c),
				std::move(r));
		}


		
		ast::expr_ptr conditionals(lex::Lexer & lexer) {
			auto l = logical_and(lexer);
			if(lexer.match(TT::QMARK)) {
				if(lexer.match(TT::QMARK)) {
					return nullco(lexer, std::move(l));
				}

				if(lexer.match(TT::COLON)) {
					return elvis(lexer, std::move(l));
				}
				
				return ternary(lexer, std::move(l));
			}
			return l;
		}
	}


	// generic expression
	ast::expr_ptr expression(lex::Lexer & lexer) {
		return conditionals(lexer);
	}
}

