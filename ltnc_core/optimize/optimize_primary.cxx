#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr primary(ast::Primary & primary) {
		if(auto call = as<ast::Call>(primary)) {
			for(auto & parameter : call->parameters) {
				parameter = optimize::expression(std::move(parameter));
			}
		}
		return nullptr;
	}
}