#include "parse.hxx"
#include <sstream>
#include "ltnc/ast/expr/Binary.hxx"
#include "ltnc/ast/expr/Ternary.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;

		ast::expr_ptr parse_nullco(Tokens & tokens, ast::expr_ptr l) {
			auto else_expr = parse_expression(tokens);
			return ast::expr::binary(
				BinaryOp::NULLCO,
				std::move(l),
				std::move(else_expr),
				location(tokens)
			);
		}



		ast::expr_ptr parse_elvis(Tokens & tokens, ast::expr_ptr l) {
			auto else_expr = parse_expression(tokens);
			return ast::expr::binary(
				BinaryOp::ELVIS,
				std::move(l),
				std::move(else_expr),
				location(tokens)
			);
		}



		ast::expr_ptr parse_ternary(Tokens & tokens, ast::expr_ptr condition) {
			auto if_expr = parse_expression(tokens);
			if(!match(TT::COLON, tokens)) {
				throw CompilerError{"Expected :", location(tokens)};
			}
			auto else_expr = parse_expression(tokens);
			return ast::expr::ternary(
				location(tokens),
				std::move(condition),
				std::move(if_expr),
				std::move(else_expr)
			);
		}
	}



	ast::expr_ptr parse_conditional(Tokens & tokens) {
		auto l = parse_binary(tokens);
		if(match(TT::QMARK, tokens)) {
			// c ?? b
			if(match(TT::QMARK, tokens)) {
				return parse_nullco(tokens, std::move(l));
			}

			// c ?: b
			if(match(TT::COLON, tokens)) {
				return parse_elvis(tokens, std::move(l));
			}
			
			// c ? a : b
			return parse_ternary(tokens, std::move(l));
		}
		return l;
	}
}

