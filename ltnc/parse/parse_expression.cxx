#include "parse.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;

		template<auto expr_fx>
		ast::expr_ptr nullco(lex::Lexer & lexer, ast::expr_ptr l) {
			auto else_expr = expr_fx(lexer);
			return std::make_unique<ast::Nullco>(
				lexer.location(),
				std::move(l),
				std::move(else_expr));
		}


		template<auto expr_fx>
		ast::expr_ptr elvis(lex::Lexer & lexer, ast::expr_ptr l) {
			auto else_expr = expr_fx(lexer);
			return std::make_unique<ast::Elvis>(
				lexer.location(),
				std::move(l),
				std::move(else_expr));
		}


		template<auto expr_fx>
		ast::expr_ptr ternary(lex::Lexer & lexer, ast::expr_ptr l) {
			auto c = expr_fx(lexer);
			if(!lexer.match(TT::COLON)) {
				throw CompilerError{"Expected :", lexer.location()};
			}
			auto r = expr_fx(lexer);
			return std::make_unique<ast::Ternary>(
				lexer.location(),
				std::move(l),
				std::move(c),
				std::move(r));
		}


		template<auto expr_fx, auto presedence_down>
		ast::expr_ptr conditionals_base(lex::Lexer & lexer) {
			auto l = presedence_down(lexer);
			if(lexer.match(TT::QMARK)) {
				// c ?? b
				if(lexer.match(TT::QMARK)) {
					return nullco<expr_fx>(lexer, std::move(l));
				}

				// c ?: b
				if(lexer.match(TT::COLON)) {
					return elvis<expr_fx>(lexer, std::move(l));
				}
				
				// c ? a : b
				return ternary<expr_fx>(lexer, std::move(l));
			}
			return l;
		}
		constexpr auto conditionals = conditionals_base<expression, binary>;
		constexpr auto static_conditionals = conditionals_base<static_expression, static_binary>;
	}


	// generic expression
	ast::expr_ptr expression(lex::Lexer & lexer) {
		return conditionals(lexer);
	}



	// generic expression
	ast::expr_ptr static_expression(lex::Lexer & lexer) {
		return static_conditionals(lexer);
	}
}

