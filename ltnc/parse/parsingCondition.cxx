#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// expression in (...) for e.g. if, while...
	ast::expr_ptr condition(lex::Lexer & lexer) {
		if(!lexer.match(TT::PAREN_L)) {
			throw CompilerError{"expected (", lexer.location()};
		}
		auto expr = expression(lexer);
		if(!lexer.match(TT::PAREN_R)) {
			throw CompilerError{"expected )", lexer.location()};
		}
		return expr;
	}
}