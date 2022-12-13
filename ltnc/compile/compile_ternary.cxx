#include "compile.hxx"
namespace ltn::c {
	ExprResult compile_expr(
		const sst::Ternary & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto name        = make_jump_id("TERNARY");
		const auto condition   = compile_expression(*expr.condition, info, scope);
		const auto if_branch   = compile_expression(*expr.if_branch, info, scope);
		const auto else_branch = compile_expression(*expr.else_branch, info, scope);
		
		const auto code = compile_conditional(
			name,
			condition.code,
			if_branch.code,
			&else_branch.code);
		
		const auto deduced_type = type::deduce_ternary(
			condition.deduced_type,
			if_branch.deduced_type,
			else_branch.deduced_type
		);

		return {
			.code = code,
			.deduced_type = deduced_type
		};
	}
}