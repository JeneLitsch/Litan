#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	using TT = Token::Type;


	// generic expr
	ast::expr_ptr parse_expression(Tokens & tokens) {
		return parse_conditional(tokens);
	}



	ast::expr_ptr parse_expression_no_cast(Tokens & tokens) {
		return parse_conditional(tokens);
	}
}

