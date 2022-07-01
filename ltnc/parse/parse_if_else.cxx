#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}



	// parses else branch and returns it if it's existing  
	ast::stmt_ptr parse_else_branch(lex::Lexer & lexer) {
		if(lexer.match(TT::ELSE)) {
			if(lexer.match(TT::PAREN_L)) {
				throw CompilerError{"else must not have a condition", lexer.location()};
			}
			return parse_statement(lexer);
		}
		return std::make_unique<ast::DoNothing>(lexer.location());
	}



	// parses if-else statement  
	ast::stmt_ptr parse_if_else(lex::Lexer & lexer) {
		if(lexer.match(TT::IF)) {
			auto expr = parse_condition(lexer); 
			auto ifBody = parse_statement(lexer); 
			auto elseBody = parse_else_branch(lexer); 
			return std::make_unique<ast::IfElse>(
				std::move(expr),
				std::move(ifBody),
				std::move(elseBody),
				lexer.location());
		}
		return nullptr;
	}
}