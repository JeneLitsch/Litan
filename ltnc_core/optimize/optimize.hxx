#pragma once
#include "ltnc_core/ast/Ast.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr unary(std::unique_ptr<ast::Unary> expr);
	ast::expr_ptr binary(std::unique_ptr<ast::Binary> expr);
	ast::expr_ptr ternary(std::unique_ptr<ast::Ternary> expr);
	ast::expr_ptr expression(ast::expr_ptr expr);

	void optimize(ast::Program & program);
}