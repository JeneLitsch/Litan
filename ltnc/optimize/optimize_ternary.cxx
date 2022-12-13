#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_conditional.hxx"
namespace ltn::c {
	sst::expr_ptr optimize_ternary(sst::Ternary & ternary) {
		ternary.condition = optimize_expression(std::move(ternary.condition));
		ternary.if_branch   = optimize_expression(std::move(ternary.if_branch));
		ternary.else_branch = optimize_expression(std::move(ternary.else_branch));

		if(auto expr = pre_decide<sst::Null>(ternary))    return expr;
		if(auto expr = pre_decide<sst::Bool>(ternary))    return expr;
		if(auto expr = pre_decide<sst::Char>(ternary))    return expr;
		if(auto expr = pre_decide<sst::Integer>(ternary)) return expr;
		if(auto expr = pre_decide<sst::Float>(ternary))   return expr;
		if(auto expr = pre_decide<sst::String>(ternary))  return expr;
		if(auto expr = pre_decide<sst::Array>(ternary))   return expr;
		return nullptr;
	}
}