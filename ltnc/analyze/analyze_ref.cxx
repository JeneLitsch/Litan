#include "analyze.hxx"
#include "ltn/casts.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::Ref & ref, Scope & scope) {
		auto expr = analyze_expression(*ref.expr, scope);
		if(auto var_expr = ltn::as<sst::Var>(*expr)) {
			return std::make_unique<sst::RefLocal>(var_expr->address);
		}
		throw CompilerError {"Cannot take reference", location(ref)};
	}



	sst::expr_ptr analyze_expr(const ast::Deref & deref, Scope & scope) {
		auto expr = analyze_expression(*deref.expr, scope);
		return std::make_unique<sst::Deref>(std::move(expr));
	}
}