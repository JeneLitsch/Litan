#pragma once
#include <tuple>
#include "stdxx/functional.hxx"
#include "stdxx/float64_t.hxx"
#include "stdxx/memory.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/tokens/Token.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/parse/BraceTracker.hxx"

namespace ltn::c {

	enum class Precedence {
		NONE,
	};

	using ParseExpr = stx::fx_ptr<ast::expr_ptr(const Token &, Tokens &)>;

	struct ExprRule {
		std::optional<ParseExpr> prefix;
		std::optional<ParseExpr> infix;
		Precedence precedence;
	};

	// Sources
	ast::Program parse(Tokens & tokens, Reporter & reporter);
	
	// Funcionals
	std::optional<ast::func_ptr> parse_functional(Tokens & tokens, const Namespace & namespaze);
	ast::enum_ptr parse_enumeration(Tokens & tokens, Namespace namespaze);
	ast::defn_ptr parse_definition(Tokens & tokens, const Namespace & namespaze);

	ast::expr_ptr parse_lambda(const Token & begin, Tokens & tokens);

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
	ast::expr_ptr parse_expr_switch(const Token & begin, Tokens & tokens);

	ast::expr_ptr parse_expression(Tokens & tokens);
	ast::expr_ptr parse_expression_no_cast(Tokens & tokens);
	ast::expr_ptr parse_conditional(Tokens & tokens);
	ast::expr_ptr parse_condition(Tokens & tokens);
	ast::expr_ptr parse_binary(Tokens & tokens);
	ast::expr_ptr parse_unary(Tokens & tokens);
	ast::expr_ptr parse_primary(Tokens & tokens);
	ast::expr_ptr parse_reflect(const Token & begin, Tokens & tokens);
	ast::expr_ptr parse_parenthesized(const Token & begin, Tokens & tokens);
	ast::expr_ptr parse_array(const Token & begin, Tokens & tokens);
	ast::expr_ptr parse_type(const Token & begin, Tokens & tokens);

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


	MemberCode parse_member_code(Tokens & tokens);
}