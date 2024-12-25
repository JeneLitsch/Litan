#include "optimize.hxx"
#include "litan_core/casts.hxx"
#include "eval/eval_conditional.hxx"
#include "litan_compiler/sst/expr/Ternary.hxx"
#include "litan_compiler/sst/expr/Literal.hxx"
#include "litan_compiler/sst/expr/Array.hxx"


namespace ltn::c {
	sst::expr_ptr optimize_ternary(sst::expr::Ternary & ternary) {
		ternary.condition = optimize_expression(std::move(ternary.condition));
		ternary.if_branch   = optimize_expression(std::move(ternary.if_branch));
		ternary.else_branch = optimize_expression(std::move(ternary.else_branch));

		if(auto expr = pre_decide<sst::expr::Null>(ternary))    return expr;
		if(auto expr = pre_decide<sst::expr::Bool>(ternary))    return expr;
		if(auto expr = pre_decide<sst::expr::Integer>(ternary)) return expr;
		if(auto expr = pre_decide<sst::expr::Float>(ternary))   return expr;
		if(auto expr = pre_decide<sst::expr::String>(ternary))  return expr;
		if(auto expr = pre_decide<sst::expr::Array>(ternary))   return expr;
		return nullptr;
	}
}