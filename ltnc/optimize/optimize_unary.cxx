#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
#include "ltnc/sst/expr/Unary.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/expr/Array.hxx"


namespace ltn::c {
	namespace {
		
		template<sst::expr::Unary::Op op>
		bool is_op_type(const sst::expr::Unary & unary) {
			return unary.op == op;
		}
		constexpr auto is_neg = is_op_type<sst::expr::Unary::Op::NEG>;
		constexpr auto is_not = is_op_type<sst::expr::Unary::Op::NOT>;
		constexpr auto is_nul = is_op_type<sst::expr::Unary::Op::NUL>;

		

		template<typename Operator, sst::expr::literal_type Litr>
		sst::expr_ptr eval(sst::expr::Expression & inner) {
			static constexpr Operator op;
			if(auto * litr = as<Litr>(inner)) {
				return op(*litr);
			}
			return nullptr;
		}
	}


	
	
	sst::expr_ptr optimize_unary(sst::expr::Unary & unary) {
		auto & inner = unary.expr;
		inner = optimize_expression(std::move(inner));
		if(is_neg(unary)) {
			if(auto expr = eval<Negation, sst::expr::Bool>(*inner))    return expr;
			if(auto expr = eval<Negation, sst::expr::Char>(*inner))    return expr;
			if(auto expr = eval<Negation, sst::expr::Integer>(*inner)) return expr;
			if(auto expr = eval<Negation, sst::expr::Float>(*inner))   return expr;
		}
		if(is_not(unary)) {
			if(auto expr = eval<Notigation, sst::expr::Bool>(*inner))    return expr;
			if(auto expr = eval<Notigation, sst::expr::Char>(*inner))    return expr;
			if(auto expr = eval<Notigation, sst::expr::Integer>(*inner)) return expr;
			if(auto expr = eval<Notigation, sst::expr::Float>(*inner))   return expr;
			if(auto expr = eval<Notigation, sst::expr::String>(*inner))  return expr;
			if(auto expr = eval<Notigation, sst::expr::Array>(*inner))   return expr;
		}
		if(is_nul(unary)) {
			if(auto expr = eval<NullTest, sst::expr::Null>(*inner))    return expr;
			if(auto expr = eval<NullTest, sst::expr::Bool>(*inner))    return expr;
			if(auto expr = eval<NullTest, sst::expr::Char>(*inner))    return expr;
			if(auto expr = eval<NullTest, sst::expr::Integer>(*inner)) return expr;
			if(auto expr = eval<NullTest, sst::expr::Float>(*inner))   return expr;
			if(auto expr = eval<NullTest, sst::expr::String>(*inner))  return expr;
			if(auto expr = eval<NullTest, sst::expr::Array>(*inner))   return expr;
		}
		return nullptr;
	}
}