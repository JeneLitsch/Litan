#include "parse.hxx"
#include "litan_compiler/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}

	// expr in (...) for e.g. if, while...
	ast::expr_ptr parse_condition(Tokens & tokens) {
		if(!match(TT::PAREN_L, tokens)) {
			throw CompilerError{"expected (", location(tokens)};
		}
		auto expr = parse_expression(tokens);
		if(!match(TT::PAREN_R, tokens)) {
			throw CompilerError{"expected )", location(tokens)};
		}
		return expr;
	}
}