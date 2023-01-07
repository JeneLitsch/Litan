#include "analyze.hxx"
#include "ltnc/type/check.hxx"

namespace ltn::c {
	// compiles any expression
	sst::expr_ptr analyze_expression(
		const ast::Expression & expr,
		Context & context,
		Scope & scope) {

		auto result = ast::visit_expression(expr, [&](const auto & e) -> sst::expr_ptr {
			return analyze_expr(e, context, scope);
		});

		if(is_error(result->type)) {
			throw CompilerError {
				"Invalid operands for expression",
				expr.location
			};
		}

		return result;
	}
}