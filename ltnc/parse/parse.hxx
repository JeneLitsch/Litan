#pragma once
#include "stdxx/float64_t.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/lex/Lexer.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
namespace ltn::c {

	// Sources
	ast::srce_ptr parse_source(lex::Lexer & lexer);
	
	// Funcionals
	ast::func_ptr parse_functional(lex::Lexer & lexer, const ast::Namespace & namespaze);
	ast::enum_ptr parse_enumeration(lex::Lexer & lexer, ast::Namespace namespaze);
	ast::glob_ptr parse_definition(lex::Lexer & lexer, const ast::Namespace & namespaze);
	ast::prst_ptr parse_preset(lex::Lexer & lexer, const ast::Namespace & namespaze);

	ast::expr_ptr parse_lambda(lex::Lexer & lexer);

	// Statements
	ast::stmt_ptr parse_statement(lex::Lexer & lexer);
	ast::stmt_ptr parse_stmt_switch(lex::Lexer & lexer);
	ast::stmt_ptr parse_block(lex::Lexer & lexer);
	ast::stmt_ptr parse_if_else(lex::Lexer & lexer);
	ast::stmt_ptr parse_while_loop(lex::Lexer & lexer);
	ast::stmt_ptr parse_for_loop(lex::Lexer & lexer);
	ast::stmt_ptr parse_just_an_expr(lex::Lexer & lexer);
	ast::stmt_ptr parse_stmt_switch(lex::Lexer & lexer);
	
	// Expressions
	ast::expr_ptr parse_assign(lex::Lexer & lexer);
	ast::expr_ptr parse_assign_r(lex::Lexer & lexer);
	ast::expr_ptr parse_expr_switch(lex::Lexer & lexer);

	ast::expr_ptr parse_expression(lex::Lexer & lexer);
	ast::expr_ptr parse_conditional(lex::Lexer & lexer);
	ast::expr_ptr parse_condition(lex::Lexer & lexer);
	ast::expr_ptr parse_binary(lex::Lexer & lexer);
	ast::expr_ptr parse_unary(lex::Lexer & lexer);
	ast::expr_ptr parse_primary(lex::Lexer & lexer);
	ast::litr_ptr parse_integral(lex::Lexer & lexer);

	ast::expr_ptr parse_static_expression(lex::Lexer & lexer);
	ast::expr_ptr parse_static_conditional(lex::Lexer & lexer);
	ast::expr_ptr parse_static_condition(lex::Lexer & lexer);
	ast::expr_ptr parse_static_binary(lex::Lexer & lexer);
	ast::expr_ptr parse_static_unary(lex::Lexer & lexer);
	ast::expr_ptr parse_static_primary(lex::Lexer & lexer);
	ast::litr_ptr parse_static_integral(lex::Lexer & lexer);

	// Utils
	std::string parse_preset_name(lex::Lexer & lexer);
	std::string parse_enum_name(lex::Lexer & lexer);
	std::string parse_definition_name(lex::Lexer & lexer);
	std::string parse_variable_name(lex::Lexer & lexer);
	std::string parse_function_name(lex::Lexer & lexer);
	std::string parse_parameter_name(lex::Lexer & lexer);
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



	template<typename op_table, auto presedence_down>
	ast::expr_ptr generic_binary(lex::Lexer & lexer) {
		auto l = presedence_down(lexer);
		while (auto op = match_op(lexer, op_table::data)) {
			auto && r = presedence_down(lexer);
			auto expr = std::make_unique<ast::Binary>(
				*op,
				std::move(l),
				std::move(r),
				lexer.location());
			l = std::move(expr);
		}				
		return l;
	}



	// Maches ; or throws
	void semicolon(lex::Lexer & lexer);
}