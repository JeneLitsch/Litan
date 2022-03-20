#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr expression(ast::expr_ptr expr) {
		if(check_unique<ast::Unary>(expr)) {
			return unary(unique_cast<ast::Unary>(std::move(expr)));
		}
		if(check_unique<ast::Binary>(expr)) {
			return binary(unique_cast<ast::Binary>(std::move(expr)));
		}
		if(check_unique<ast::Ternary>(expr)) {
			return ternary(unique_cast<ast::Ternary>(std::move(expr)));
		}
		return expr;
	}


	void optimize(ast::Program & program) {
		for(auto & global : program.globals) {
			global->expr = expression(std::move(global->expr));
		}
	}

}