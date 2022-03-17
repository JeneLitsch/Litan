#pragma once
#include "ltn/float64_t.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/lex/Lexer.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
namespace ltn::c::parse {

	// Sources
	ast::prog_ptr source(lex::Lexer & lexer);
	
	// Funcionals
	ast::func_ptr functional(lex::Lexer & lexer, const ast::Namespace & namespaze);
	ast::enum_ptr enumeration(lex::Lexer & lexer);

	ast::expr_ptr lambda(lex::Lexer & lexer);

	// Statements
	ast::stmt_ptr statement(lex::Lexer & lexer);
	ast::stmt_ptr block(lex::Lexer & lexer);
	ast::stmt_ptr if_else(lex::Lexer & lexer);
	ast::stmt_ptr while_loop(lex::Lexer & lexer);
	ast::stmt_ptr for_loop(lex::Lexer & lexer);
	
	// Expressions
	ast::expr_ptr expression(lex::Lexer & lexer);
	ast::expr_ptr condition(lex::Lexer & lexer);
	ast::expr_ptr unary(lex::Lexer & lexer);
	ast::expr_ptr index(lex::Lexer & lexer);
	ast::expr_ptr primary(lex::Lexer & lexer);
	ast::expr_ptr assign(lex::Lexer & lexer);
	ast::expr_ptr assign_r(lex::Lexer & lexer);
	ast::expr_ptr factor(lex::Lexer & lexer);
	ast::expr_ptr term(lex::Lexer & lexer);
	ast::expr_ptr comparision(lex::Lexer & lexer);
	ast::expr_ptr equality(lex::Lexer & lexer);
	ast::expr_ptr logical_or(lex::Lexer & lexer);
	ast::expr_ptr logical_and(lex::Lexer & lexer);
	ast::expr_ptr integral(lex::Lexer & lexer);

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

	// Maches ; or throws
	inline void semicolon(lex::Lexer & lexer);
}