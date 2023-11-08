#include "analyze.hxx"
#include <string_view>
#include "ltnc/sst/expr/Literal.hxx"


namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::Integer & expr, Scope &) {
		return sst::integer(expr.value);
	}



	sst::expr_ptr analyze_expr(const ast::Float & expr, Scope &) {
		return sst::floating(expr.value);
	}



	sst::expr_ptr analyze_expr(const ast::Bool & expr, Scope &) {
		return sst::boolean(expr.value);
	}



	sst::expr_ptr analyze_expr(const ast::Null &, Scope &) {
		return sst::null();
	}


	sst::expr_ptr analyze_expr(const ast::Char & expr, Scope &) {
		return sst::character(expr.value);
	}



	sst::expr_ptr analyze_expr(const ast::String & expr, Scope &) {
		return sst::string(expr.value);
	}
}