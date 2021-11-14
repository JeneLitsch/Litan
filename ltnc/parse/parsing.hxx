#pragma once
#include "ltnc/ast/Function.hxx"
#include "ltnc/ast/Statement.hxx"
#include "ltnc/lex/Lexer.hxx"
namespace ltn::c::parse {

	std::unique_ptr<ast::Function> function(lex::Lexer & lexer);

	std::unique_ptr<ast::Statement> statement(lex::Lexer & lexer);
	std::unique_ptr<ast::Block> block(lex::Lexer & lexer);
	std::unique_ptr<ast::IfElse> ifElse(lex::Lexer & lexer);
	std::unique_ptr<ast::While> whileLoop(lex::Lexer & lexer);
	
	std::unique_ptr<ast::Expression> expression(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> condition(lex::Lexer & lexer);
}