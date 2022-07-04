#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c {
	ast::expr_ptr optimize_expression(ast::Expression & expr) {
		if(auto e = as<ast::Primary>(expr)) {
			return optimize_primary(*e);
		}
		if(auto e = as<ast::Unary>(expr)) {
			return optimize_unary(*e);
		}
		if(auto e = as<ast::Binary>(expr)) {
			return optimize_binary(*e);
		}
		if(auto e = as<ast::Ternary>(expr)) {
			return optimize_ternary(*e);
		}
		return nullptr;
	}



	ast::expr_ptr optimize_expression(ast::expr_ptr expr) {
		if(auto e = optimize_expression(*expr)) {
			return e;
		}
		return expr;
	}
}