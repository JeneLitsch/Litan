#include "parse.hxx"
#include "ltnc_core/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}


	void brace_l(lex::Lexer & lexer) {
		if(!lexer.match(TT::BRACE_L)) {
			throw CompilerError{"Expected {", lexer.location()};
		}
	}



	void brace_r(lex::Lexer & lexer) {
		if(!lexer.match(TT::BRACE_R)) {
			throw CompilerError{"Expected }", lexer.location()};
		}
	}
}