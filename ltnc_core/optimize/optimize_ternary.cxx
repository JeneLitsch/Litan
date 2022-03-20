#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr ternary(std::unique_ptr<ast::Ternary> expr) {
		expr->condition = expression(std::move(expr->condition));
		expr->if_expr   = expression(std::move(expr->if_expr));
		expr->else_expr = expression(std::move(expr->else_expr));
		return expr;
	}
}