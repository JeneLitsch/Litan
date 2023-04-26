#pragma once
#include "stdxx/functional.hxx"
#include "stdxx/float64_t.hxx"
#include "stdxx/memory.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/tokens/Token.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/type/Type.hxx"
#include "ltnc/parse/BraceTracker.hxx"

namespace ltn::c {

	// Sources
	ast::Program parse(Tokens & tokens, Reporter & reporter);
	
	// Funcionals
	std::optional<ast::func_ptr> parse_functional(Tokens & tokens, const Namespace & namespaze);
	ast::enum_ptr parse_enumeration(Tokens & tokens, Namespace namespaze);
	ast::defn_ptr parse_definition(Tokens & tokens, const Namespace & namespaze);
	ast::prst_ptr parse_preset(Tokens & tokens, const Namespace & namespaze);

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
	
	// Expressions
	ast::expr_ptr parse_assign_r(Tokens & tokens);
	ast::expr_ptr parse_expr_switch(Tokens & tokens);

	ast::expr_ptr parse_expression(Tokens & tokens);
	ast::expr_ptr parse_expression_no_cast(Tokens & tokens);
	ast::expr_ptr parse_conditional(Tokens & tokens);
	ast::expr_ptr parse_condition(Tokens & tokens);
	ast::expr_ptr parse_binary(Tokens & tokens);
	ast::expr_ptr parse_unary(Tokens & tokens);
	ast::expr_ptr parse_primary(Tokens & tokens);
	ast::expr_ptr parse_reflect(Tokens & tokens);
	ast::expr_ptr parse_parenthesized(Tokens & tokens);
	ast::expr_ptr parse_integral(Tokens & tokens);
	ast::expr_ptr parse_array(Tokens & tokens);

	// Utils
	std::string parse_preset_name(Tokens & tokens);
	std::string parse_enum_name(Tokens & tokens);
	std::string parse_variable_name(Tokens & tokens);
	std::string parse_function_name(Tokens & tokens);
	std::string parse_parameter_name(Tokens & tokens);
	void brace_l(Tokens & tokens);
	void brace_r(Tokens & tokens);

	std::vector<std::optional<type::IncompleteType>> parse_placeholder(Tokens & tokens);

	// Maches ; or throws
	void semicolon(Tokens & tokens);

	std::pair<std::string, Namespace> parse_symbol(Tokens & tokens);

	type::IncompleteType parse_type(Tokens & tokens);
	type::IncompleteType parse_type(Tokens & tokens, BraceTracker & brace_tracker);
	std::optional<type::IncompleteType> parse_var_type_auto(Tokens & tokens);
	type::IncompleteType parse_var_type(Tokens & tokens);
	ast::Parameter::DeclType parse_parameter_type(Tokens & tokens);
	type::IncompleteType parse_return_type(Tokens & tokens);
}