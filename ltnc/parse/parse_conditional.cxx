#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		using TT = Token::Type;

		template<auto expr_fx>
		ast::Expression parse_nullco(Tokens & tokens, ast::Expression l) {
			auto else_expr = expr_fx(tokens);
			return ast::Binary {
				.location = location(tokens),
				.op = BinaryOp::NULLCO,
				.l = std::move(l),
				.r = std::move(else_expr),
			};
		}



		template<auto expr_fx>
		ast::Expression parse_elvis(Tokens & tokens, ast::Expression l) {
			auto else_expr = expr_fx(tokens);
			return ast::Binary {
				.location = location(tokens),
				.op = BinaryOp::ELVIS,
				.l = std::move(l),
				.r = std::move(else_expr),
			};
		}



		template<auto expr_fx>
		ast::Expression parse_ternary(Tokens & tokens, ast::Expression l) {
			auto c = expr_fx(tokens);
			if(!match(TT::COLON, tokens)) {
				throw CompilerError{"Expected :", location(tokens)};
			}
			auto r = expr_fx(tokens);
			return ast::Ternary {
				.location = location(tokens),
				.condition = std::move(l),
				.if_branch = std::move(c),
				.else_branch = std::move(r),
			};
		}
	}



	ast::Expression parse_conditional(Tokens & tokens) {
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

