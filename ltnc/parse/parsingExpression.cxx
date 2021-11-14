#include "parsing.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	std::unique_ptr<ast::Expression> expression(lex::Lexer & lexer) {
		return equality(lexer);
	}
}

