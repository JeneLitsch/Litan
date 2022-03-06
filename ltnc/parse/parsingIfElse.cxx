#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}


	// parses else branch and returns it if it's existing  
	std::unique_ptr<ast::Statement> else_branch(lex::Lexer & lexer) {
		if(lexer.match(TT::ELSE)) {
			if(lexer.match(TT::PAREN_L)) {
				throw CompilerError{"else must not have a condition", lexer.location()};
			}
			return statement(lexer);
		}
		return nullptr;
	}


	// parses if-else statement  
	std::unique_ptr<ast::IfElse> if_else(lex::Lexer & lexer) {
		if(lexer.match(TT::IF)) {
			auto expr = condition(lexer); 
			auto ifBody = statement(lexer); 
			auto elseBody = else_branch(lexer); 
			return std::make_unique<ast::IfElse>(
				std::move(expr),
				std::move(ifBody),
				std::move(elseBody),
				lexer.location());
		}
		return nullptr;
	}
}