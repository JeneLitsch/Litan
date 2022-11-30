#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	using TT = Token::Type;

	// generic expression
	ast::expr_ptr parse_expression(Tokens & tokens) {
		auto expr = parse_conditional(tokens);
		// if(auto colon = match(TT::COLON, tokens)) {
		// 	auto type = parse_type(tokens);
		// 	return std::make_unique<ast::TypedUnary>(
		// 		ast::TypedUnary::Op::STATIC_CAST,
		// 		type,
		// 		std::move(expr),
		// 		colon->location 
		// 	);
		// }
		return expr;
	}
}

