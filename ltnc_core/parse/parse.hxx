#pragma once
#include "ltn/float64_t.hxx"
#include "ltnc_core/ast/Ast.hxx"
#include "ltnc_core/lex/Lexer.hxx"
#include "ltnc_core/CompilerError.hxx"
#include "ltnc_core/Reporter.hxx"
namespace ltn::c::parse {

	// Sources
	ast::srce_ptr source(lex::Lexer & lexer);
	
	// Funcionals
	ast::func_ptr functional(lex::Lexer & lexer, const ast::Namespace & namespaze);
	ast::enum_ptr enumeration(lex::Lexer & lexer, ast::Namespace namespaze);
	ast::glob_ptr definition(lex::Lexer & lexer, const ast::Namespace & namespaze);
	ast::prst_ptr preset(lex::Lexer & lexer, const ast::Namespace & namespaze);

	ast::expr_ptr lambda(lex::Lexer & lexer);

	// Statements
	ast::stmt_ptr statement(lex::Lexer & lexer);
	ast::stmt_ptr stmt_switch(lex::Lexer & lexer);
	ast::stmt_ptr block(lex::Lexer & lexer);
	ast::stmt_ptr if_else(lex::Lexer & lexer);
	ast::stmt_ptr while_loop(lex::Lexer & lexer);
	ast::stmt_ptr for_loop(lex::Lexer & lexer);
	ast::stmt_ptr just_an_expr(lex::Lexer & lexer);
	ast::stmt_ptr stmt_switch(lex::Lexer & lexer);
	
	// Expressions
	ast::expr_ptr assign(lex::Lexer & lexer);
	ast::expr_ptr assign_r(lex::Lexer & lexer);
	ast::expr_ptr expr_switch(lex::Lexer & lexer);

	ast::expr_ptr expression(lex::Lexer & lexer);
	ast::expr_ptr functional_op(lex::Lexer & lexer);
	ast::expr_ptr conditional(lex::Lexer & lexer);
	ast::expr_ptr condition(lex::Lexer & lexer);
	ast::expr_ptr binary(lex::Lexer & lexer);
	ast::expr_ptr unary(lex::Lexer & lexer);
	ast::expr_ptr primary(lex::Lexer & lexer);
	ast::litr_ptr integral(lex::Lexer & lexer);

	ast::expr_ptr static_expression(lex::Lexer & lexer);
	ast::expr_ptr static_functional_op(lex::Lexer & lexer);
	ast::expr_ptr static_conditional(lex::Lexer & lexer);
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