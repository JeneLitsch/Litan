#include "compile.hxx"
namespace ltn::c {
	ExprCode compile_ternary(const ast::Ternary & expr, CompilerInfo & info, Scope & scope) {
		const auto name        = make_jump_id("TERNARY");
		const auto condition   = compile_expression(*expr.condition, info, scope).code;
		const auto if_branch   = compile_expression(*expr.if_branch, info, scope).code;
		const auto else_branch = compile_expression(*expr.else_branch, info, scope).code;
		
		const auto code = compile_conditional(
			name,
			condition,
			if_branch,
			&else_branch);
		
		return ExprCode{code};
	}
}