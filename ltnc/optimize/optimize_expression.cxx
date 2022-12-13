#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c {
	sst::expr_ptr optimize_expression(sst::Expression & expr) {
		if(auto e = as<sst::Primary>(expr)) {
			return optimize_primary(*e);
		}
		if(auto e = as<sst::Unary>(expr)) {
			return optimize_unary(*e);
		}
		if(auto e = as<sst::Binary>(expr)) {
			return optimize_binary(*e);
		}
		if(auto e = as<sst::Ternary>(expr)) {
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