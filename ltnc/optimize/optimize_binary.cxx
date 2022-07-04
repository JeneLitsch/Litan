#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_binary.hxx"
namespace ltn::c {
	namespace {
		template<ast::Binary::Type op>
		bool is_op_type(const ast::Binary & binary) {
			return binary.type == op;
		}
		constexpr auto is_add = is_op_type<ast::Binary::Type::ADD>;
		constexpr auto is_sub = is_op_type<ast::Binary::Type::SUB>;
		constexpr auto is_mlt = is_op_type<ast::Binary::Type::MLT>;
		constexpr auto is_div = is_op_type<ast::Binary::Type::DIV>;
		constexpr auto is_mod = is_op_type<ast::Binary::Type::MOD>;
	}



	template<
		typename Operator,
		ast::literal_type LitrL,
		ast::literal_type LitrR>
	ast::expr_ptr eval(
		const ast::Expression & expr_l,
		const ast::Expression & expr_r) {
		
		static constexpr Operator op;
		auto * l = as<LitrL>(expr_l);
		auto * r = as<LitrR>(expr_r);
		if(l && r) {
			return op(*l, *r);
		}
		return nullptr;
	}


	template<typename Op>
	ast::expr_ptr eval_arith(
		const ast::Expression & l,
		const ast::Expression & r) {
		
		if(auto expr = eval<Op, ast::Bool,    ast::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, ast::Bool,    ast::Char>(l, r))    return expr;
		if(auto expr = eval<Op, ast::Bool,    ast::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, ast::Bool,    ast::Float>(l, r))   return expr;

		if(auto expr = eval<Op, ast::Char,    ast::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, ast::Char,    ast::Char>(l, r))    return expr;
		if(auto expr = eval<Op, ast::Char,    ast::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, ast::Char,    ast::Float>(l, r))   return expr;

		if(auto expr = eval<Op, ast::Integer, ast::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, ast::Integer, ast::Char>(l, r))    return expr;
		if(auto expr = eval<Op, ast::Integer, ast::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, ast::Integer, ast::Float>(l, r))   return expr;

		if(auto expr = eval<Op, ast::Float,   ast::Bool>(l, r))    return expr;
		if(auto expr = eval<Op, ast::Float,   ast::Char>(l, r))    return expr;
		if(auto expr = eval<Op, ast::Float,   ast::Integer>(l, r)) return expr;
		if(auto expr = eval<Op, ast::Float,   ast::Float>(l, r))   return expr;

		return nullptr;
	}



	ast::expr_ptr optimize_binary(ast::Binary & binary) {
		auto & l = binary.l;
		auto & r = binary.r;
		l = optimize_expression(std::move(l));
		r = optimize_expression(std::move(r));
		
		if(is_add(binary)) {
			if(auto expr = eval_arith<Addition>(*l, *r)) return expr;
			if(auto expr = eval<Addition, ast::String,  ast::String>(*l, *r))  return expr;
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