#include "analyze.hxx"
#include "ltnc/sst/expr/Ternary.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::Ternary & expr, Scope & scope) {
		
		auto condition   = analyze_expression(*expr.condition, scope);
		auto if_branch   = analyze_expression(*expr.if_branch, scope);
		auto else_branch = analyze_expression(*expr.else_branch, scope);

		return sst::expr::ternary(std::move(condition), std::move(if_branch), std::move(else_branch));
	}
}