#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}



	// parses else branch and returns it if it's existing  
	ast::stmt_ptr parse_else_branch(Tokens & tokens) {
		if(match(TT::ELSE, tokens)) {
			if(match(TT::PAREN_L, tokens)) {
				throw CompilerError{"else must not have a condition", location(tokens)};
			}
			return parse_statement(tokens);
		}
		return std::make_unique<ast::DoNothing>(location(tokens));
	}



	// parses if-else statement  
	ast::stmt_ptr parse_if_else(Tokens & tokens) {
		if(match(TT::IF, tokens)) {
			auto expr = parse_condition(tokens); 
			auto ifBody = parse_statement(tokens); 
			auto elseBody = parse_else_branch(tokens); 
			return std::make_unique<ast::IfElse>(
				std::move(expr),
				std::move(ifBody),
				std::move(elseBody),
				location(tokens));
		}
		return nullptr;
	}
}