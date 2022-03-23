#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
namespace ltn::c::optimize {
	template<typename ConditionNode>
	ast::expr_ptr decide(ast::Ternary & expr) {
		if(auto * litr = as<ConditionNode>(*expr.condition)) {
			if(litr->value) {
				return std::move(expr.if_expr);
			}
			else {
				return std::move(expr.else_expr);
			}
		}
		return nullptr;
	} 

	template<>
	ast::expr_ptr decide<ast::String>(ast::Ternary & expr) {
		if(auto * litr = as<ast::String>(*expr.condition)) {
			return std::move(expr.if_expr);
		}
		return nullptr;
	} 

	template<>
	ast::expr_ptr decide<ast::Array>(ast::Ternary & expr) {
		if(auto * litr = as<ast::String>(*expr.condition)) {
			return std::move(expr.if_expr);
		}
		return nullptr;
	} 

	template<>
	ast::expr_ptr decide<ast::Null>(ast::Ternary & expr) {
		if(auto * litr = as<ast::String>(*expr.condition)) {
			return std::move(expr.else_expr);
		}
		return nullptr;
	} 

	ast::expr_ptr ternary(ast::Ternary & ternary) {
		ternary.condition = expression(std::move(ternary.condition));
		ternary.if_expr   = expression(std::move(ternary.if_expr));
		ternary.else_expr = expression(std::move(ternary.else_expr));

		if(auto expr = decide<ast::Bool>(ternary))    return expr;
		if(auto expr = decide<ast::Char>(ternary))    return expr;
		if(auto expr = decide<ast::Integer>(ternary)) return expr;
		if(auto expr = decide<ast::Float>(ternary))   return expr;
		if(auto expr = decide<ast::Float>(ternary))   return expr;
		if(auto expr = decide<ast::String>(ternary))  return expr;
		if(auto expr = decide<ast::Array>(ternary))   return expr;

		return nullptr;
	}
}