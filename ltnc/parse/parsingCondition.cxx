#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	std::unique_ptr<ast::Expression> condition(lex::Lexer & lexer) {
		if(!lexer.match(TT::PAREN_L)) {
			throw CompilerError{"expected (", lexer.inLine()};
		}
		if(!lexer.match(TT::PAREN_R)) {
			throw CompilerError{"expected )", lexer.inLine()};
		}
		return nullptr;
	}
}