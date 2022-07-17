#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;

		template<auto expr_fx>
		ast::expr_ptr parse_nullco(LexBuffer & lexer, ast::expr_ptr l) {
			auto else_expr = expr_fx(lexer);
			return std::make_unique<ast::Binary>(
				ast::Binary::Type::NULLCO,
				std::move(l),
				std::move(else_expr),
				lexer.location());
		}



		template<auto expr_fx>
		ast::expr_ptr parse_elvis(LexBuffer & lexer, ast::expr_ptr l) {
			auto else_expr = expr_fx(lexer);
			return std::make_unique<ast::Binary>(
				ast::Binary::Type::ELVIS,
				std::move(l),
				std::move(else_expr),
				lexer.location());
		}



		template<auto expr_fx>
		ast::expr_ptr parse_ternary(LexBuffer & lexer, ast::expr_ptr l) {
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
		ast::expr_ptr parse_conditional_base(LexBuffer & lexer) {
			auto l = presedence_down(lexer);
			if(lexer.match(TT::QMARK)) {
				// c ?? b
				if(lexer.match(TT::QMARK)) {
					return parse_nullco<expr_fx>(lexer, std::move(l));
				}

				// c ?: b
				if(lexer.match(TT::COLON)) {
					return parse_elvis<expr_fx>(lexer, std::move(l));
				}
				
				// c ? a : b
				return parse_ternary<expr_fx>(lexer, std::move(l));
			}
			return l;
		}
	}



	ast::expr_ptr parse_conditional(LexBuffer & lexer) {
		return parse_conditional_base<parse_expression, parse_binary>(lexer);
	}



	ast::expr_ptr parse_static_conditional(LexBuffer & lexer) {
		return parse_conditional_base<parse_static_expression, parse_static_binary>(lexer);
	}
}

