#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	// template<typename Node, auto fx>
	// ast::expr_ptr attempt(ast::expr_ptr expr) {
	// 	if(check_unique<Node>(expr)) {
	// 		return fx(static_unique_cast<Node>(std::move(expr)));
	// 	}
	// 	return nullptr;
	// }

	




	ast::expr_ptr expression(ast::expr_ptr expr) {
		if(check_unique<ast::Unary>(expr)) {
			return unary(unique_cast<ast::Unary>(std::move(expr)));
		}
		return expr;
	}


	void optimize(ast::Program & program) {
		for(auto & global : program.globals) {
			global->expr = expression(std::move(global->expr));
		}
	}

}