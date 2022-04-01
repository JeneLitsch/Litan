#pragma once
#include "ltn/float64_t.hxx"
#include "ltnc_core/ast/Ast.hxx"
#include "ltnc_core/lex/Lexer.hxx"
#include "ltnc_core/CompilerError.hxx"
#include "ltnc_core/Reporter.hxx"
namespace ltn::c::parse {

	// Sources
	ast::prog_ptr source(lex::Lexer & lexer);
	
	// Funcionals
	ast::func_ptr functional(lex::Lexer & lexer, const ast::Namespace & namespaze);
	std::vector<ast::glob_ptr> enumeration(lex::Lexer & lexer, ast::Namespace namespaze);
	ast::glob_ptr definition(lex::Lexer & lexer, const ast::Namespace & namespaze);
	ast::prst_ptr preset(lex::Lexer & lexer, const ast::Namespace & namespaze);

	ast::expr_ptr lambda(lex::Lexer & lexer);

	// Statements
	ast::stmt_ptr statement(lex::Lexer & lexer);
	ast::stmt_ptr block(lex::Lexer & lexer);
	ast::stmt_ptr if_else(lex::Lexer & lexer);
	ast::stmt_ptr while_loop(lex::Lexer & lexer);
	ast::stmt_ptr for_loop(lex::Lexer & lexer);
	
	// Expressions
	ast::expr_ptr assign(lex::Lexer & lexer);
	ast::expr_ptr assign_r(lex::Lexer & lexer);

	ast::expr_ptr expression(lex::Lexer & lexer);
	ast::expr_ptr condition(lex::Lexer & lexer);
	ast::expr_ptr binary(lex::Lexer & lexer);
	ast::expr_ptr unary(lex::Lexer & lexer);
	ast::expr_ptr primary(lex::Lexer & lexer);
	ast::litr_ptr integral(lex::Lexer & lexer);

	ast::expr_ptr static_expression(lex::Lexer & lexer);
	ast::expr_ptr static_condition(lex::Lexer & lexer);
	ast::expr_ptr static_binary(lex::Lexer & lexer);
	ast::expr_ptr static_unary(lex::Lexer & lexer);
	ast::expr_ptr static_primary(lex::Lexer & lexer);
	ast::litr_ptr static_integral(lex::Lexer & lexer);

	// Utils
	std::string preset_name(lex::Lexer & lexer);
	std::string enum_name(lex::Lexer & lexer);
	std::string definition_name(lex::Lexer & lexer);
	std::string variable_name(lex::Lexer & lexer);
	std::string function_name(lex::Lexer & lexer);
	std::string parameter_name(lex::Lexer & lexer);
	void brace_l(lex::Lexer & lexer);
	void brace_r(lex::Lexer & lexer);



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
	void semicolon(lex::Lexer & lexer);
}