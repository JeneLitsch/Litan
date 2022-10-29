#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
namespace ltn::c {
	ast::expr_ptr optimize_primary(ast::Primary & primary) {
		if(auto call = as<ast::Call>(primary)) {
			for(auto & parameter : call->parameters) {
				parameter = optimize_expression(std::move(parameter));
			}
		}
		return nullptr;
	}
}