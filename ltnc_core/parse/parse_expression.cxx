#include "parse.hxx"
#include <sstream>
namespace ltn::c::parse {
	// generic expression
	ast::expr_ptr expression(lex::Lexer & lexer) {
		return functional_op(lexer);
	}



	// generic expression
	ast::expr_ptr static_expression(lex::Lexer & lexer) {
		return static_functional_op(lexer);
	}
}

