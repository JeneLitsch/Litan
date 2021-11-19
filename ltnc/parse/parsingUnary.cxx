#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Unary::Type;
	}


	std::unique_ptr<ast::Expression> unary(lex::Lexer & lexer) {
		if(lexer.match(TT::MINUS)) {
			return std::make_unique<ast::Unary>(OP::NEG, unary(lexer), lexer.debug());
		}
		if(lexer.match(TT::NOT)) {
			return std::make_unique<ast::Unary>(OP::NOT, unary(lexer), lexer.debug());
		}
		return primary(lexer);
	}
}

