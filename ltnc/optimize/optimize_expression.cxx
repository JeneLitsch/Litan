#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "ltnc/sst/expr/Binary.hxx"
#include "ltnc/sst/expr/Ternary.hxx"
#include "ltnc/sst/expr/Unary.hxx"
#include "ltnc/sst/expr/Call.hxx"

namespace ltn::c {
	sst::expr_ptr optimize_expression(sst::expr::Expression & expr) {
		if(auto call = as<sst::expr::Call>(expr)) {
			for(auto & argument : call->arguments) {
				argument = optimize_expression(std::move(argument));
			}
		}
		if(auto e = as<sst::expr::Unary>(expr)) {
			return optimize_unary(*e);
		}
		if(auto e = as<sst::expr::Binary>(expr)) {
			return optimize_binary(*e);
		}
		if(auto e = as<sst::expr::Ternary>(expr)) {
			return optimize_ternary(*e);
		}
		return nullptr;
	}



	sst::expr_ptr optimize_expression(sst::expr_ptr expr) {
		if(auto e = optimize_expression(*expr)) {
			return e;
		}
		return expr;
	}
}