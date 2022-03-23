#pragma once
#include "ltnc_core/ast/Ast.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr unary(ast::Unary & unary);
	ast::expr_ptr binary(ast::Binary & binary);
	ast::expr_ptr ternary(ast::Ternary & ternary);
	ast::expr_ptr expression(ast::expr_ptr expr);

	void optimize(ast::Program & program);
}