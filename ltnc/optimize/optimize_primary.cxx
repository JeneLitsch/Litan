#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
namespace ltn::c {
	sst::expr_ptr optimize_primary(sst::Primary & primary) {
		if(auto call = as<sst::Call>(primary)) {
			for(auto & parameter : call->parameters) {
				parameter = optimize_expression(std::move(parameter));
			}
		}
		return nullptr;
	}
}