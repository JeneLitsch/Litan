#pragma once
#include "ltnc/ast/Ast.hxx"
namespace ltn::c {
	struct OptimizerInfo {
		
	};

	ast::expr_ptr optimize_primary(ast::Primary & primary);
	ast::expr_ptr optimize_unary(ast::Unary & unary);
	ast::expr_ptr optimize_binary(ast::Binary & binary);
	ast::expr_ptr optimize_ternary(ast::Ternary & ternary);
	ast::expr_ptr optimize_expression(ast::Expression & expr);
	ast::expr_ptr optimize_expression(ast::expr_ptr expr);

	ast::stmt_ptr optimize_statement(ast::Statement & stmt);
	ast::stmt_ptr optimize_statement(ast::stmt_ptr stmt);

	void optimize_global(ast::Global & global);
	void optimize_function(ast::Function & function);


	void optimize(ast::Program & program);

}