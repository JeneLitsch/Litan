#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
namespace ltn::c {
	namespace {
		
		template<sst::Unary::Type op>
		bool is_op_type(const sst::Unary & unary) {
			return unary.type == op;
		}
		constexpr auto is_neg = is_op_type<sst::Unary::Type::NEG>;
		constexpr auto is_not = is_op_type<sst::Unary::Type::NOT>;
		constexpr auto is_nul = is_op_type<sst::Unary::Type::NUL>;

		

		template<typename Operator, sst::literal_type Litr>
		sst::expr_ptr eval(sst::Expression & inner) {
			static constexpr Operator op;
			if(auto * litr = as<Litr>(inner)) {
				return op(*litr);
			}
			return nullptr;
		}
	}


	
	
	sst::expr_ptr optimize_unary(sst::Unary & unary) {
		auto & inner = unary.expression;
		inner = optimize_expression(std::move(inner));
		if(is_neg(unary)) {
			if(auto expr = eval<Negation, sst::Bool>(*inner))    return expr;
			if(auto expr = eval<Negation, sst::Char>(*inner))    return expr;
			if(auto expr = eval<Negation, sst::Integer>(*inner)) return expr;
			if(auto expr = eval<Negation, sst::Float>(*inner))   return expr;
		}
		if(is_not(unary)) {
			if(auto expr = eval<Notigation, sst::Bool>(*inner))    return expr;
			if(auto expr = eval<Notigation, sst::Char>(*inner))    return expr;
			if(auto expr = eval<Notigation, sst::Integer>(*inner)) return expr;
			if(auto expr = eval<Notigation, sst::Float>(*inner))   return expr;
			if(auto expr = eval<Notigation, sst::String>(*inner))  return expr;
			if(auto expr = eval<Notigation, sst::Array>(*inner))   return expr;
		}
		if(is_nul(unary)) {
			if(auto expr = eval<NullTest, sst::Null>(*inner))    return expr;
			if(auto expr = eval<NullTest, sst::Bool>(*inner))    return expr;
			if(auto expr = eval<NullTest, sst::Char>(*inner))    return expr;
			if(auto expr = eval<NullTest, sst::Integer>(*inner)) return expr;
			if(auto expr = eval<NullTest, sst::Float>(*inner))   return expr;
			if(auto expr = eval<NullTest, sst::String>(*inner))  return expr;
			if(auto expr = eval<NullTest, sst::Array>(*inner))   return expr;
		}
		return nullptr;
	}
}