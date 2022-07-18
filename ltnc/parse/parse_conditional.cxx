#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		using TT = Token::Type;

		template<auto expr_fx>
		ast::expr_ptr parse_nullco(Tokens & tokens, ast::expr_ptr l) {
			auto else_expr = expr_fx(tokens);
			return std::make_unique<ast::Binary>(
				ast::Binary::Type::NULLCO,
				std::move(l),
				std::move(else_expr),
				location(tokens));
		}



		template<auto expr_fx>
		ast::expr_ptr parse_elvis(Tokens & tokens, ast::expr_ptr l) {
			auto else_expr = expr_fx(tokens);
			return std::make_unique<ast::Binary>(
				ast::Binary::Type::ELVIS,
				std::move(l),
				std::move(else_expr),
				location(tokens));
		}



		template<auto expr_fx>
		ast::expr_ptr parse_ternary(Tokens & tokens, ast::expr_ptr l) {
			auto c = expr_fx(tokens);
			if(!match(TT::COLON, tokens)) {
				throw CompilerError{"Expected :", location(tokens)};
			}
			auto r = expr_fx(tokens);
			return std::make_unique<ast::Ternary>(
				location(tokens),
				std::move(l),
				std::move(c),
				std::move(r));
		}



		template<auto expr_fx, auto presedence_down>
		ast::expr_ptr parse_conditional_base(Tokens & tokens) {
			auto l = presedence_down(tokens);
			if(match(TT::QMARK, tokens)) {
				// c ?? b
				if(match(TT::QMARK, tokens)) {
					return parse_nullco<expr_fx>(tokens, std::move(l));
				}

				// c ?: b
				if(match(TT::COLON, tokens)) {
					return parse_elvis<expr_fx>(tokens, std::move(l));
				}
				
				// c ? a : b
				return parse_ternary<expr_fx>(tokens, std::move(l));
			}
			return l;
		}
	}



	ast::expr_ptr parse_conditional(Tokens & tokens) {
		return parse_conditional_base<parse_expression, parse_binary>(tokens);
	}



	ast::expr_ptr parse_static_conditional(Tokens & tokens) {
		return parse_conditional_base<parse_static_expression, parse_static_binary>(tokens);
	}
}

