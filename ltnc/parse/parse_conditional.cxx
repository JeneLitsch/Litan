#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		using TT = Token::Type;

		template<auto expr_fx>
		ast::expr_ptr parse_nullco(Tokens & tokens, ast::expr_ptr l) {
			auto else_expr = expr_fx(tokens);
			return stx::make_unique<ast::Binary>(
				ast::Binary::Type::NULLCO,
				std::move(l),
				std::move(else_expr),
				location(tokens)
			);
		}



		template<auto expr_fx>
		ast::expr_ptr parse_elvis(Tokens & tokens, ast::expr_ptr l) {
			auto else_expr = expr_fx(tokens);
			return stx::make_unique<ast::Binary>(
				ast::Binary::Type::ELVIS,
				std::move(l),
				std::move(else_expr),
				location(tokens)
			);
		}



		template<auto expr_fx>
		ast::expr_ptr parse_ternary(Tokens & tokens, ast::expr_ptr l) {
			auto c = expr_fx(tokens);
			if(!match(TT::COLON, tokens)) {
				throw CompilerError{"Expected :", location(tokens)};
			}
			auto r = expr_fx(tokens);
			return stx::make_unique<ast::Ternary>(
				location(tokens),
				std::move(l),
				std::move(c),
				std::move(r)
			);
		}
	}



	ast::expr_ptr parse_conditional(Tokens & tokens) {
		auto l = parse_binary(tokens);
		if(match(TT::QMARK, tokens)) {
			// c ?? b
			if(match(TT::QMARK, tokens)) {
				return parse_nullco<parse_expression>(tokens, std::move(l));
			}

			// c ?: b
			if(match(TT::COLON, tokens)) {
				return parse_elvis<parse_expression>(tokens, std::move(l));
			}
			
			// c ? a : b
			return parse_ternary<parse_expression_no_cast>(tokens, std::move(l));
		}
		return l;
	}
}

