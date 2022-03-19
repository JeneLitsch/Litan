#pragma once
#include "ltnc_core/ast/Ast.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr expression(ast::expr_ptr expr);
	ast::expr_ptr unary(std::unique_ptr<ast::Unary> unary);

	void optimize(ast::Program & program);
}