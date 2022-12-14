#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_binary.hxx"
namespace ltn::c {
	namespace {
		template<sst::Binary::Op op>
		bool is_op_type(const sst::Binary & binary) {
			return binary.op == op;
		}
		constexpr auto is_add = is_op_type<sst::Binary::Op::ADD>;
		constexpr auto is_sub = is_op_type<sst::Binary::Op::SUB>;
		constexpr auto is_mlt = is_op_type<sst::Binary::Op::MLT>;
		constexpr auto is_div = is_op_type<sst::Binary::Op::DIV>;
		constexpr auto is_mod = is_op_type<sst::Binary::Op::MOD>;
	}



	template<
		typename Operator,
		sst::literal_type LitrL,
		sst::literal_type LitrR>
	sst::expr_ptr eval(
		const sst::Expression & expr_l,
		const sst::Expression & expr_r) {
		
		static constexpr Operator op;
		auto * l = as<LitrL>(expr_l);
		auto * r = as<LitrR>(expr_r);
		if(l && r) {
			return op(*l, *r);
		}
		return nullptr;
	}


	template<typename Op>
	sst::expr_ptr eval_arith(
		const sst::Expression & l,
		const sst::Expression & r) {
		
		if(auto expr = eval<Op, sst::Bool,    sst::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, sst::Bool,    sst::Char>(l, r))    return expr;
		if(auto expr = eval<Op, sst::Bool,    sst::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, sst::Bool,    sst::Float>(l, r))   return expr;

		if(auto expr = eval<Op, sst::Char,    sst::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, sst::Char,    sst::Char>(l, r))    return expr;
		if(auto expr = eval<Op, sst::Char,    sst::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, sst::Char,    sst::Float>(l, r))   return expr;

		if(auto expr = eval<Op, sst::Integer, sst::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, sst::Integer, sst::Char>(l, r))    return expr;
		if(auto expr = eval<Op, sst::Integer, sst::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, sst::Integer, sst::Float>(l, r))   return expr;

		if(auto expr = eval<Op, sst::Float,   sst::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, sst::Float,   sst::Char>(l, r))    return expr;
		if(auto expr = eval<Op, sst::Float,   sst::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, sst::Float,   sst::Float>(l, r))   return expr;

		return nullptr;
	}



	sst::expr_ptr optimize_binary(sst::Binary & binary) {
		auto & l = binary.l;
		auto & r = binary.r;
		l = optimize_expression(std::move(l));
		r = optimize_expression(std::move(r));
		
		if(is_add(binary)) {
			if(auto expr = eval_arith<Addition>(*l, *r)) return expr;
			if(auto expr = eval<Addition, sst::String,  sst::String>(*l, *r))  return expr;
		}

		if(is_sub(binary)) {
			if(auto expr = eval_arith<Subtraction>(*l, *r)) return expr;
		}

		if(is_mlt(binary)) {
			if(auto expr = eval_arith<Multiply>(*l, *r)) return expr;
		}

		if(is_div(binary)) {
			if(auto expr = eval_arith<Divide>(*l, *r)) return expr;
		}

		if(is_mod(binary)) {
			if(auto expr = eval_arith<Modulo>(*l, *r)) return expr;
		}

		return nullptr;
	}
}