#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_conditional.hxx"
namespace ltn::c {
	ast::expr_ptr optimize_ternary(ast::Ternary & ternary) {
		ternary.condition = optimize_expression(std::move(ternary.condition));
		ternary.if_branch   = optimize_expression(std::move(ternary.if_branch));
		ternary.else_branch = optimize_expression(std::move(ternary.else_branch));

		if(auto expr = pre_decide<ast::Null>(ternary))    return expr;
		if(auto expr = pre_decide<ast::Bool>(ternary))    return expr;
		if(auto expr = pre_decide<ast::Char>(ternary))    return expr;
		if(auto expr = pre_decide<ast::Integer>(ternary)) return expr;
		if(auto expr = pre_decide<ast::Float>(ternary))   return expr;
		if(auto expr = pre_decide<ast::String>(ternary))  return expr;
		if(auto expr = pre_decide<ast::Array>(ternary))   return expr;
		return nullptr;
	}
}