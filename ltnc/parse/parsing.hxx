#pragma once
#include "ltn/float64_t.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/lex/Lexer.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
namespace ltn::c::parse {

	// Sources
	std::vector<std::unique_ptr<ast::Functional>> source(lex::Lexer & lexer);
	
	// Funcionals
	std::unique_ptr<ast::Functional> functional(
		lex::Lexer & lexer,
		const ast::Namespace & namespaze);

	std::unique_ptr<ast::Lambda> lambda(lex::Lexer & lexer);

	// Statements
	std::unique_ptr<ast::Statement> statement(lex::Lexer & lexer);
	std::unique_ptr<ast::Block> block(lex::Lexer & lexer);
	std::unique_ptr<ast::IfElse> if_else(lex::Lexer & lexer);
	std::unique_ptr<ast::While> while_loop(lex::Lexer & lexer);
	std::unique_ptr<ast::For> for_loop(lex::Lexer & lexer);
	
	// Expressions
	std::unique_ptr<ast::Expression> expression(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> condition(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> unary(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> index(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> primary(lex::Lexer & lexer);

	std::unique_ptr<ast::Expression> assign(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> assign_r(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> factor(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> term(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> comparision(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> equality(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> logical_or(lex::Lexer & lexer);
	std::unique_ptr<ast::Expression> logical_and(lex::Lexer & lexer);

	// Utils
	std::string variable_name(lex::Lexer & lexer);
	std::string function_name(lex::Lexer & lexer);
	std::string parameter_name(lex::Lexer & lexer);

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

	auto match_op(
		lex::Lexer & lexer,
		const auto & op_table) -> std::optional<decltype(op_table.front().second)> {
		for(const auto & [tt, op] : op_table) {
			if(lexer.match(tt)) {
				return op;
			}
		}
		return std::nullopt;
	}
}