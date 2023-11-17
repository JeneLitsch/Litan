#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include "ltnc/ast/expr/Unary.hxx"
#include "ltnc/sst/expr/Unary.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Unary & unary, Scope & scope) {
		
		auto expr = analyze_expression(*unary.expr, scope);
		const auto op = static_cast<sst::expr::Unary::Op>(unary.op);

		return sst::expr::unary(op, std::move(expr));
	}
}