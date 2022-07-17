#pragma once
#include "stdxx/float64_t.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/lex/LexBuffer.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
namespace ltn::c {

	// Sources
	ast::srce_ptr parse_source(LexBuffer & lexer);
	
	// Funcionals
	ast::func_ptr parse_functional(LexBuffer & lexer, const ast::Namespace & namespaze);
	ast::enum_ptr parse_enumeration(LexBuffer & lexer, ast::Namespace namespaze);
	ast::glob_ptr parse_definition(LexBuffer & lexer, const ast::Namespace & namespaze);
	ast::prst_ptr parse_preset(LexBuffer & lexer, const ast::Namespace & namespaze);

	ast::expr_ptr parse_lambda(LexBuffer & lexer);

	// Statements
	ast::stmt_ptr parse_statement(LexBuffer & lexer);
	ast::stmt_ptr parse_stmt_switch(LexBuffer & lexer);
	ast::stmt_ptr parse_block(LexBuffer & lexer);
	ast::stmt_ptr parse_if_else(LexBuffer & lexer);
	ast::stmt_ptr parse_while_loop(LexBuffer & lexer);
	ast::stmt_ptr parse_for_loop(LexBuffer & lexer);
	ast::stmt_ptr parse_just_an_expr(LexBuffer & lexer);
	ast::stmt_ptr parse_stmt_switch(LexBuffer & lexer);
	
	// Expressions
	ast::expr_ptr parse_assign(LexBuffer & lexer);
	ast::expr_ptr parse_assign_r(LexBuffer & lexer);
	ast::expr_ptr parse_expr_switch(LexBuffer & lexer);

	ast::expr_ptr parse_expression(LexBuffer & lexer);
	ast::expr_ptr parse_conditional(LexBuffer & lexer);
	ast::expr_ptr parse_condition(LexBuffer & lexer);
	ast::expr_ptr parse_binary(LexBuffer & lexer);
	ast::expr_ptr parse_unary(LexBuffer & lexer);
	ast::expr_ptr parse_primary(LexBuffer & lexer);
	ast::litr_ptr parse_integral(LexBuffer & lexer);

	ast::expr_ptr parse_static_expression(LexBuffer & lexer);
	ast::expr_ptr parse_static_conditional(LexBuffer & lexer);
	ast::expr_ptr parse_static_condition(LexBuffer & lexer);
	ast::expr_ptr parse_static_binary(LexBuffer & lexer);
	ast::expr_ptr parse_static_unary(LexBuffer & lexer);
	ast::expr_ptr parse_static_primary(LexBuffer & lexer);
	ast::litr_ptr parse_static_integral(LexBuffer & lexer);

	// Utils
	std::string parse_preset_name(LexBuffer & lexer);
	std::string parse_enum_name(LexBuffer & lexer);
	std::string parse_definition_name(LexBuffer & lexer);
	std::string parse_variable_name(LexBuffer & lexer);
	std::string parse_function_name(LexBuffer & lexer);
	std::string parse_parameter_name(LexBuffer & lexer);
	void brace_l(LexBuffer & lexer);
	void brace_r(LexBuffer & lexer);



	auto match_op(
		LexBuffer & lexer,
		const auto & op_table) -> std::optional<decltype(op_table.front().second)> {
		for(const auto & [tt, op] : op_table) {
			if(lexer.match(tt)) {
				return op;
			}
		}
		return std::nullopt;
	}



	template<typename op_table, auto presedence_down>
	ast::expr_ptr generic_binary(LexBuffer & lexer) {
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
	void semicolon(LexBuffer & lexer);
}