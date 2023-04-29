#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::expr_ptr parse_cast(Tokens & tokens, ast::expr_ptr expr) {
			const auto make = [&] (ast::TypedUnary::Op op) {
				auto type = parse_type(tokens);
				const auto loc = location(*expr);
				return parse_cast(tokens, std::make_unique<ast::TypedUnary>(
					op, 
					std::move(type),
					std::move(expr),
					loc
				));
			};
			if(match(TT::COLON, tokens)) {
				if(match(TT::STAR, tokens)) {
					return make(ast::TypedUnary::Op::STATIC_COPY);
				}
				else {
					return make(ast::TypedUnary::Op::STATIC_CAST);
				}
			}
			if(match(TT::TILDE, tokens)) {
				if(match(TT::STAR, tokens)) {
					return make(ast::TypedUnary::Op::DYNAMIC_COPY);
				}
				else {
					return make(ast::TypedUnary::Op::DYNAMIC_CAST);
				}
			}
			if(match(TT::XMARK, tokens)) {
				if(match(TT::STAR, tokens)) {
					return make(ast::TypedUnary::Op::FORCE_COPY);
				}
				else {
					return make(ast::TypedUnary::Op::FORCE_CAST);
				}
			}
			return expr;
		}
	}


	// generic expr
	ast::expr_ptr parse_expression(Tokens & tokens) {
		auto expr = parse_expression_no_cast(tokens);
		return parse_cast(tokens, std::move(expr));

	}



	ast::expr_ptr parse_expression_no_cast(Tokens & tokens) {
		return parse_conditional(tokens);
	}
}

