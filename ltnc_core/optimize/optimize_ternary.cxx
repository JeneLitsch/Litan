#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
namespace ltn::c::optimize {
	ast::expr_ptr ternary(ast::Ternary & expr) {
		expr.condition = expression(std::move(expr.condition));
		expr.if_expr   = expression(std::move(expr.if_expr));
		expr.else_expr = expression(std::move(expr.else_expr));

		if(auto * litr = as<ast::Bool>(*expr.condition)) {
			if(litr->value) return std::move(expr.if_expr);
			else return std::move(expr.else_expr);
		}

		if(auto * litr = as<ast::Char>(*expr.condition)) {
			if(litr->value) return std::move(expr.if_expr);
			else return std::move(expr.else_expr);
		}

		if(auto * litr = as<ast::Integer>(*expr.condition)) {
			if(litr->value) return std::move(expr.if_expr);
			else return std::move(expr.else_expr);
		}

		if(auto * litr = as<ast::Float>(*expr.condition)) {
			if(litr->value) return std::move(expr.if_expr);
			else return std::move(expr.else_expr);
		}

		if(auto * litr = as<ast::String>(*expr.condition)) {
			return std::move(expr.if_expr);
		}

		if(auto * litr = as<ast::Array>(*expr.condition)) {
			return std::move(expr.if_expr);
		}

		return nullptr;
	}
}