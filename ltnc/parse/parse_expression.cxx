#include "parse.hxx"
#include <sstream>
namespace ltn::c::parse {
	// generic expression
	ast::expr_ptr expression(lex::Lexer & lexer) {
		return conditional(lexer);
	}



	// generic expression
	ast::expr_ptr static_expression(lex::Lexer & lexer) {
		return static_conditional(lexer);
	}
}

