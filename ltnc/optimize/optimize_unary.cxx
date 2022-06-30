#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
namespace ltn::c::optimize {
	namespace {
		template<ast::Unary::Type op>
		bool is_op_type(const ast::Unary & unary) {
			return unary.type == op;
		}
		constexpr auto is_neg = is_op_type<ast::Unary::Type::NEG>;
		constexpr auto is_not = is_op_type<ast::Unary::Type::NOT>;
		constexpr auto is_nul = is_op_type<ast::Unary::Type::NUL>;

		

		template<typename Operator, ast::literal_type Litr>
		ast::expr_ptr eval(ast::Expression & inner) {
			static constexpr Operator op;
			if(auto * litr = as<Litr>(inner)) {
				return op(*litr);
			}
			return nullptr;
		}
	}


	
	
	ast::expr_ptr unary(ast::Unary & unary) {
		auto & inner = unary.expression;
		inner = expression(std::move(inner));
		if(is_neg(unary)) {
			if(auto expr = eval<Negation, ast::Bool>(*inner))    return expr;
			if(auto expr = eval<Negation, ast::Char>(*inner))    return expr;
			if(auto expr = eval<Negation, ast::Integer>(*inner)) return expr;
			if(auto expr = eval<Negation, ast::Float>(*inner))   return expr;
		}
		if(is_not(unary)) {
			if(auto expr = eval<Notigation, ast::Bool>(*inner))    return expr;
			if(auto expr = eval<Notigation, ast::Char>(*inner))    return expr;
			if(auto expr = eval<Notigation, ast::Integer>(*inner)) return expr;
			if(auto expr = eval<Notigation, ast::Float>(*inner))   return expr;
			if(auto expr = eval<Notigation, ast::String>(*inner))  return expr;
			if(auto expr = eval<Notigation, ast::Array>(*inner))   return expr;
		}
		if(is_nul(unary)) {
			if(auto expr = eval<NullTest, ast::Null>(*inner))    return expr;
			if(auto expr = eval<NullTest, ast::Bool>(*inner))    return expr;
			if(auto expr = eval<NullTest, ast::Char>(*inner))    return expr;
			if(auto expr = eval<NullTest, ast::Integer>(*inner)) return expr;
			if(auto expr = eval<NullTest, ast::Float>(*inner))   return expr;
			if(auto expr = eval<NullTest, ast::String>(*inner))  return expr;
			if(auto expr = eval<NullTest, ast::Array>(*inner))   return expr;
		}
		return nullptr;
	}
}