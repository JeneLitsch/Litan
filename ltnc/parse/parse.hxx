#pragma once
#include "stdxx/float64_t.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/tokens/Token.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
namespace ltn::c {

	// Sources
	ast::srce_ptr parse_source(Tokens & tokens);
	
	// Funcionals
	ast::func_ptr parse_functional(Tokens & tokens, const ast::Namespace & namespaze);
	ast::enum_ptr parse_enumeration(Tokens & tokens, ast::Namespace namespaze);
	ast::defn_ptr parse_definition(Tokens & tokens, const ast::Namespace & namespaze);
	ast::prst_ptr parse_preset(Tokens & tokens, const ast::Namespace & namespaze);

	ast::expr_ptr parse_lambda(Tokens & tokens);

	// Statements
	ast::stmt_ptr parse_statement(Tokens & tokens);
	ast::stmt_ptr parse_stmt_switch(Tokens & tokens);
	ast::stmt_ptr parse_block(Tokens & tokens);
	ast::stmt_ptr parse_if_else(Tokens & tokens);
	ast::stmt_ptr parse_while_loop(Tokens & tokens);
	ast::stmt_ptr parse_for_loop(Tokens & tokens);
	ast::stmt_ptr parse_just_an_expr(Tokens & tokens);
	ast::stmt_ptr parse_stmt_switch(Tokens & tokens);
	
	// Expressions
	ast::expr_ptr parse_assign(Tokens & tokens);
	ast::expr_ptr parse_assign_r(Tokens & tokens);
	ast::expr_ptr parse_expr_switch(Tokens & tokens);

	ast::expr_ptr parse_expression(Tokens & tokens);
	ast::expr_ptr parse_conditional(Tokens & tokens);
	ast::expr_ptr parse_condition(Tokens & tokens);
	ast::expr_ptr parse_binary(Tokens & tokens);
	ast::expr_ptr parse_unary(Tokens & tokens);
	ast::expr_ptr parse_primary(Tokens & tokens);
	ast::litr_ptr parse_integral(Tokens & tokens);

	// Utils
	std::string parse_preset_name(Tokens & tokens);
	std::string parse_enum_name(Tokens & tokens);
	std::string parse_definition_name(Tokens & tokens);
	std::string parse_variable_name(Tokens & tokens);
	std::string parse_function_name(Tokens & tokens);
	std::string parse_parameter_name(Tokens & tokens);
	void brace_l(Tokens & tokens);
	void brace_r(Tokens & tokens);



	auto match_op(
		Tokens & tokens,
		const auto & op_table) -> std::optional<decltype(op_table.front().second)> {
		for(const auto & [tt, op] : op_table) {
			if(match(tt, tokens)) {
				return op;
			}
		}
		return std::nullopt;
	}



	template<typename op_table, auto presedence_down>
	ast::expr_ptr generic_binary(Tokens & tokens) {
		auto l = presedence_down(tokens);
		while (auto op = match_op(tokens, op_table::data)) {
			auto && r = presedence_down(tokens);
			auto expr = std::make_unique<ast::Binary>(
				*op,
				std::move(l),
				std::move(r),
				location(tokens));
			l = std::move(expr);
		}				
		return l;
	}



	// Maches ; or throws
	void semicolon(Tokens & tokens);
}