#include "parsing.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// generic expression
	std::unique_ptr<ast::Expression> expression(lex::Lexer & lexer) {
		return equality(lexer);
	}
}

