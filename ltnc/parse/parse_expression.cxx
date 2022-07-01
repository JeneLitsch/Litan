#include "parse.hxx"
#include <sstream>
namespace ltn::c {
	// generic expression
	ast::expr_ptr parse_expression(lex::Lexer & lexer) {
		return parse_conditional(lexer);
	}



	// generic expression
	ast::expr_ptr parse_static_expression(lex::Lexer & lexer) {
		return parse_static_conditional(lexer);
	}
}

