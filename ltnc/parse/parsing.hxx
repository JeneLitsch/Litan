#pragma once
#include "ltnc/ast/Function.hxx"
#include "ltnc/ast/Statement.hxx"
#include "ltnc/lex/Lexer.hxx"
namespace ltnc::parse {

	std::unique_ptr<ast::Function> function(lex::Lexer & lexer);


	std::unique_ptr<ast::Statement> statement(lex::Lexer & lexer);
	std::unique_ptr<ast::Block> block(lex::Lexer & lexer);
	std::unique_ptr<ast::IfElse> ifElse(lex::Lexer & lexer);
	std::unique_ptr<ast::While> whileLoop(lex::Lexer & lexer);
	
	std::unique_ptr<ast::Expression> condition(lex::Lexer & lexer);
}