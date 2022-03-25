#pragma once
#include "ltnc_core/ast/Ast.hxx"
namespace ltn::c::optimize {
	struct OptimizerInfo {
		
	};

	ast::expr_ptr primary(ast::Primary & primary);
	ast::expr_ptr unary(ast::Unary & unary);
	ast::expr_ptr binary(ast::Binary & binary);
	ast::expr_ptr ternary(ast::Ternary & ternary);
	ast::expr_ptr expression(ast::Expression & expr);
	ast::expr_ptr expression(ast::expr_ptr expr);

	ast::stmt_ptr statement(ast::Statement & stmt);
	ast::stmt_ptr statement(ast::stmt_ptr stmt);

	void global(ast::Global & global);
	void function(ast::Function & function);


	void optimize(ast::Program & program);

}