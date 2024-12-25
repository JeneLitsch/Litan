#pragma once
#include <tuple>
#include "stdxx/functional.hxx"
#include "stdxx/float64_t.hxx"
#include "stdxx/memory.hxx"
#include "litan_compiler/ast/AST.hxx"
#include "litan_compiler/tokens/Token.hxx"
#include "litan_compiler/CompilerError.hxx"
#include "litan_compiler/parse/BraceTracker.hxx"
#include "litan_compiler/source/Source.hxx"

namespace ltn::c {

	// Sources
	ast::Program parse(const std::vector<Source> & sources);
	
	// Funcionals
	ast::func_ptr parse_function(Tokens & tokens, const Namespace & namespaze);
	ast::enum_ptr parse_enumeration(Tokens & tokens, Namespace namespaze);
	ast::defn_ptr parse_definition(Tokens & tokens, const Namespace & namespaze);

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
	ast::stmt_ptr parse_newvar(Tokens & tokens);
	ast::stmt_ptr parse_conditional_stmt(Tokens & tokens);
	
	// Expressions
	ast::expr_ptr parse_assign_r(Tokens & tokens);
	ast::expr_ptr parse_expr_switch(Tokens & tokens);

	ast::expr_ptr parse_expression(Tokens & tokens);
	ast::expr_ptr parse_ternary(Tokens & tokens);
	ast::expr_ptr parse_condition(Tokens & tokens);
	ast::expr_ptr parse_binary(Tokens & tokens);
	ast::expr_ptr parse_unary(Tokens & tokens);
	ast::expr_ptr parse_primary(Tokens & tokens);
	ast::expr_ptr parse_reflect(Tokens & tokens);
	ast::expr_ptr parse_parenthesized(Tokens & tokens);
	ast::expr_ptr parse_integral(Tokens & tokens);
	ast::expr_ptr parse_array(Tokens & tokens);
	ast::expr_ptr parse_conditional_expr(Tokens & tokens);


	ast::bind_ptr parse_binding(const Token & start, Tokens & tokens);
	
	// Utils
	std::string parse_preset_name(Tokens & tokens);
	std::string parse_enum_name(Tokens & tokens);
	std::string parse_variable_name(Tokens & tokens);
	std::string parse_function_name(Tokens & tokens);
	std::string parse_parameter_name(Tokens & tokens);
	void brace_l(Tokens & tokens);
	void brace_r(Tokens & tokens);

	std::tuple<std::uint64_t, bool> parse_placeholder(Tokens & tokens);

	// Maches ; or throws
	void semicolon(Tokens & tokens);

	std::pair<std::string, Namespace> parse_symbol(Tokens & tokens);

	ast::expr_ptr parse_type(Tokens & tokens);

	std::string parse_member(Tokens & tokens);
}