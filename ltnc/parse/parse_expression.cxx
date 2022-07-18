#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	// generic expression
	ast::expr_ptr parse_expression(Tokens & tokens) {
		return parse_conditional(tokens);
	}



	// generic expression
	ast::expr_ptr parse_static_expression(Tokens & tokens) {
		return parse_static_conditional(tokens);
	}
}

