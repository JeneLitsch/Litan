#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltnc::parse {
	namespace {
		using TT = ltnc::lex::Token::Type;
	}

	std::unique_ptr<ast::While> whileLoop(lex::Lexer & lexer) {
		if(lexer.match(TT::WHILE)) {
			auto expr = condition(lexer);
			auto body = statement(lexer);
		}
		return nullptr;
	}
}