#pragma once
#include "ltnc/ast/Ast.hxx"
#include "ltnc/lex/Lexer.hxx"
#include "ltnc/CompilerError.hxx"
namespace ltn::c::parse {

	// Sources
	std::vector<std::unique_ptr<ast::Functional>> source(lex::Lexer & lexer);
	
	// Funcionals
	std::unique_ptr<ast::Functional> functional(
		lex::Lexer & lexer,
		const ast::Namespace & nameSpace);

	std::unique_ptr<ast::Lambda> lambda(lex::Lexer & lexer);

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
	std::unique_ptr<ast::Expression> logOr(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> logAnd(lex::Lexer & lexer);

	// Utils
	std::string variableName(lex::Lexer & lexer);
	std::string functionName(lex::Lexer & lexer);
	std::string parameterName(lex::Lexer & lexer);


	// // Error catching
	// auto attempt(auto fx, auto & errors, lex::Lexer & lexer, const ast::Namespace & ns) 
	// 	-> decltype(fx(lexer, ns)) {
	// 	try {
	// 		return fx(lexer, ns);;
	// 	}
	// 	catch(const CompilerError & error) {
	// 		errors.push(error);
	// 		lexer.sync();
	// 		return nullptr;
	// 	}
	// }

	auto attempt(auto fx, auto & errors, lex::Lexer & lexer)
		-> decltype(fx(lexer)) {
		try {
			return fx(lexer);
		}
		catch(const CompilerError & error) {
			errors.push(error);
			lexer.sync();
			return nullptr;
		}
	}
}