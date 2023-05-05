#include "analyze.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::Unary & unary, Scope & scope) {
		
		auto expr = analyze_expression(*unary.expr, scope);
		const auto op = static_cast<sst::Unary::Op>(unary.op);

		return std::make_unique<sst::Unary>(op, std::move(expr));
	}
}