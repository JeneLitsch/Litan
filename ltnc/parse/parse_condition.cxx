#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// expression in (...) for e.g. if, while...
	ast::expr_ptr parse_condition(lex::Lexer & lexer) {
		if(!lexer.match(TT::PAREN_L)) {
			throw CompilerError{"expected (", lexer.location()};
		}
		auto expr = parse_expression(lexer);
		if(!lexer.match(TT::PAREN_R)) {
			throw CompilerError{"expected )", lexer.location()};
		}
		return expr;
	}
}