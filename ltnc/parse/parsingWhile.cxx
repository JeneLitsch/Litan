#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	std::unique_ptr<ast::While> whileLoop(lex::Lexer & lexer) {
		if(lexer.match(TT::WHILE)) {
			auto expr = condition(lexer);
			auto body = statement(lexer);
			return std::make_unique<ast::While>(std::move(expr), std::move(body));
		}
		return nullptr;
	}
}