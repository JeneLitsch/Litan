#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	using TT = Token::Type;

	// generic expression
	ast::expr_ptr parse_expression(Tokens & tokens) {
		auto expr = parse_expression_no_cast(tokens);
		if(auto colon = match(TT::COLON, tokens)) {
			auto type = parse_type(tokens);
			return std::make_unique<ast::TypedUnary>(
				ast::TypedUnary::Op::STATIC_CAST,
				type,
				std::move(expr),
				colon->location 
			);
		}
		if(auto tilde = match(TT::TILDE, tokens)) {
			auto type = parse_type(tokens);
			return std::make_unique<ast::TypedUnary>(
				ast::TypedUnary::Op::DYNAMIC_CAST,
				type,
				std::move(expr),
				tilde->location 
			);
		}
		else return expr;
	}



	ast::expr_ptr parse_expression_no_cast(Tokens & tokens) {
		return parse_conditional(tokens);
	}
}

