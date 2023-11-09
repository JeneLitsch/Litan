#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_binary.hxx"
#include "ltnc/sst/expr/Binary.hxx"
#include "ltnc/sst/expr/Literal.hxx"


namespace ltn::c {
	namespace {
		template<sst::expr::Binary::Op op>
		bool is_op_type(const sst::expr::Binary & binary) {
			return binary.op == op;
		}
		constexpr auto is_add = is_op_type<sst::expr::Binary::Op::ADD>;
		constexpr auto is_sub = is_op_type<sst::expr::Binary::Op::SUB>;
		constexpr auto is_mlt = is_op_type<sst::expr::Binary::Op::MLT>;
		constexpr auto is_div = is_op_type<sst::expr::Binary::Op::DIV>;
		constexpr auto is_mod = is_op_type<sst::expr::Binary::Op::MOD>;
	}



	template<
		typename Operator,
		sst::expr::literal_type LitrL,
		sst::expr::literal_type LitrR>
	sst::expr_ptr eval(
		const sst::expr::Expression & expr_l,
		const sst::expr::Expression & expr_r) {
		
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
		const sst::expr::Expression & l,
		const sst::expr::Expression & r) {
		
		if(auto expr = eval<Op, sst::expr::Bool,    sst::expr::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, sst::expr::Bool,    sst::expr::Char>(l, r))    return expr;
		if(auto expr = eval<Op, sst::expr::Bool,    sst::expr::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, sst::expr::Bool,    sst::expr::Float>(l, r))   return expr;

		if(auto expr = eval<Op, sst::expr::Char,    sst::expr::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, sst::expr::Char,    sst::expr::Char>(l, r))    return expr;
		if(auto expr = eval<Op, sst::expr::Char,    sst::expr::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, sst::expr::Char,    sst::expr::Float>(l, r))   return expr;

		if(auto expr = eval<Op, sst::expr::Integer, sst::expr::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, sst::expr::Integer, sst::expr::Char>(l, r))    return expr;
		if(auto expr = eval<Op, sst::expr::Integer, sst::expr::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, sst::expr::Integer, sst::expr::Float>(l, r))   return expr;

		if(auto expr = eval<Op, sst::expr::Float,   sst::expr::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, sst::expr::Float,   sst::expr::Char>(l, r))    return expr;
		if(auto expr = eval<Op, sst::expr::Float,   sst::expr::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, sst::expr::Float,   sst::expr::Float>(l, r))   return expr;

		return nullptr;
	}



	sst::expr_ptr optimize_binary(sst::expr::Binary & binary) {
		auto & l = binary.l;
		auto & r = binary.r;
		l = optimize_expression(std::move(l));
		r = optimize_expression(std::move(r));

		try {
			if(is_add(binary)) {
				if(auto expr = eval_arith<Addition>(*l, *r)) return expr;
				if(auto expr = eval<Addition, sst::expr::String,  sst::expr::String>(*l, *r))  return expr;
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
		}
		catch(...) {}
		

		return nullptr;
	}
}