#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr expression(ast::Expression & expr) {
		if(auto e = as<ast::Unary>(expr)) {
			return unary(*e);
		}
		if(auto e = as<ast::Binary>(expr)) {
			return binary(*e);
		}
		if(auto e = as<ast::Ternary>(expr)) {
			return ternary(*e);
		}
		return nullptr;
	}



	ast::expr_ptr expression(ast::expr_ptr expr) {
		if(auto e = expression(*expr)) {
			return e;
		}
		return expr;
	}



	void optimize(ast::Program & program) {
		for(auto & global : program.globals) {
			global->expr = expression(std::move(global->expr));
		}
	}

}