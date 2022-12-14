#include "compile.hxx"
namespace ltn::c {
	sst::expr_ptr analyze_expr(
		const ast::Ternary & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto condition   = analyze_expression(*expr.condition, info, scope);
		const auto if_branch   = analyze_expression(*expr.if_branch, info, scope);
		const auto else_branch = analyze_expression(*expr.else_branch, info, scope);

		const auto deduced_type = type::deduce_ternary(
			condition->type,
			if_branch->type,
			else_branch->type
		);

		return std::make_unique<sst::Ternary>(
			deduced_type,
			std::move(condition),
			std::move(if_branch),
			std::move(else_branch)
		);
	}
}