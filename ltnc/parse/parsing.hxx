#pragma once
#include "ltnc/ast/Function.hxx"
#include "ltnc/ast/Source.hxx"
#include "ltnc/ast/Statement.hxx"
#include "ltnc/ast/Assignable.hxx"
#include "ltnc/ast/Literals.hxx"
#include "ltnc/lex/Lexer.hxx"

namespace ltn::c::parse {

	// Sources
	std::unique_ptr<ast::Source> source(lex::Lexer & lexer);
	
	// Funcionals
	std::unique_ptr<ast::Functional> functional(
		lex::Lexer & lexer,
		const ast::Namespace & nameSpace);

	// Statements
	std::unique_ptr<ast::Statement> statement(lex::Lexer & lexer);
	std::unique_ptr<ast::Block> block(lex::Lexer & lexer);
	std::unique_ptr<ast::IfElse> ifElse(lex::Lexer & lexer);
	std::unique_ptr<ast::While> whileLoop(lex::Lexer & lexer);
	std::unique_ptr<ast::For> forLoop(lex::Lexer & lexer);
	

	// Expressions
	std::unique_ptr<ast::Expression> expression(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> condition(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> unary(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> index(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> primary(lex::Lexer & lexer);

	std::unique_ptr<ast::Expression> assign(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> assignR(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> factor(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> term(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> comparision(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> equality(lex::Lexer & lexer);	

	// Utils
	std::string variableName(lex::Lexer & lexer);
	std::string functionName(lex::Lexer & lexer);
	std::string parameterName(lex::Lexer & lexer);
}