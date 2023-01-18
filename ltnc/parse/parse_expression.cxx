#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::expr_ptr parse_cast(Tokens & tokens, ast::expr_ptr expr) {
			const auto make = [&] (ast::TypedUnary::Op op) {
				auto type = parse_type(tokens);
				const auto loc = expr->location;
				return stx::make_unique<ast::TypedUnary>(
					op, 
					type,
					std::move(expr),
					loc
				);
			};
			if(match(TT::COLON, tokens)) {
				return make(ast::TypedUnary::Op::STATIC_CAST);
			}
			if(match(TT::TILDE, tokens)) {
				return make(ast::TypedUnary::Op::DYNAMIC_CAST);
			}
			return expr;
		}
	}


	// generic expression
	ast::expr_ptr parse_expression(Tokens & tokens) {
		auto expr = parse_expression_no_cast(tokens);
		return parse_cast(tokens, std::move(expr));

	}



	ast::expr_ptr parse_expression_no_cast(Tokens & tokens) {
		return parse_conditional(tokens);
	}
}

