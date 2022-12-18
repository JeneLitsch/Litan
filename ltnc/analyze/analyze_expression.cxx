#include "analyze.hxx"


namespace ltn::c {
	// compiles any expression
	sst::expr_ptr analyze_expression(
		const ast::Expression & expr,
		Context & context,
		Scope & scope) {

		return ast::visit_expression(expr, [&](const auto & e) -> sst::expr_ptr {
			return analyze_expr(e, context, scope);
		});
	}




}