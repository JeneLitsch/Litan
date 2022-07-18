#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// expression in (...) for e.g. if, while...
	ast::expr_ptr parse_condition(Tokens & tokens) {
		if(!match(TT::PAREN_L, tokens)) {
			throw CompilerError{"expected (", tokens.location()};
		}
		auto expr = parse_expression(tokens);
		if(!match(TT::PAREN_R, tokens)) {
			throw CompilerError{"expected )", tokens.location()};
		}
		return expr;
	}
}