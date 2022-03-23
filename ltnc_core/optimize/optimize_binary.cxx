#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr binary(ast::Binary & expr) {
		expr.l = expression(std::move(expr.l));
		expr.r = expression(std::move(expr.r));
		return nullptr;
	}
}