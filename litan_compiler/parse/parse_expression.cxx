#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	using TT = Token::Type;


	ast::expr_ptr parse_expression(Tokens & tokens) {
		return parse_ternary(tokens);
	}
}

