#include "analyze.hxx"
#include <string_view>
#include "ltnc/ast/expr/Bool.hxx"
#include "ltnc/ast/expr/Char.hxx"
#include "ltnc/ast/expr/Float.hxx"
#include "ltnc/ast/expr/Integer.hxx"
#include "ltnc/ast/expr/String.hxx"
#include "ltnc/sst/expr/Literal.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Integer & expr, Scope &) {
		return sst::expr::integer(expr.value);
	}



	sst::expr_ptr analyze_expr(const ast::expr::Float & expr, Scope &) {
		return sst::expr::floating(expr.value);
	}



	sst::expr_ptr analyze_expr(const ast::expr::Bool & expr, Scope &) {
		return sst::expr::boolean(expr.value);
	}



	sst::expr_ptr analyze_expr(const ast::expr::Null &, Scope &) {
		return sst::expr::null();
	}


	sst::expr_ptr analyze_expr(const ast::expr::Char & expr, Scope &) {
		return sst::expr::character(expr.value);
	}



	sst::expr_ptr analyze_expr(const ast::expr::String & expr, Scope &) {
		return sst::expr::string(expr.value);
	}
}