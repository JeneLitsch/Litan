#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltnc::parse {
	namespace {
		using TT = ltnc::lex::Token::Type;
	}

	std::unique_ptr<ast::Statement> elseBranch(lex::Lexer & lexer) {
		if(lexer.match(TT::ELSE)) {
			return statement(lexer);
		}
		return nullptr;
	}

	std::unique_ptr<ast::IfElse> ifElse(lex::Lexer & lexer) {
		if(lexer.match(TT::IF)) {
			auto expr = condition(lexer); 
			auto ifBody = statement(lexer); 
			auto elseBody = elseBranch(lexer); 
			return std::make_unique<ast::IfElse>(
				std::move(expr),
				std::move(ifBody),
				std::move(elseBody));
		}
		return nullptr;
	}
}