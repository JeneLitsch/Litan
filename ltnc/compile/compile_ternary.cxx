#include "compile.hxx"
namespace ltn::c::compile {
	ExprCode ternary(const ast::Ternary & expr, CompilerInfo & info, Scope & scope) {
		const auto name        = make_jump_id("TERNARY");
		const auto condition   = expression(*expr.condition, info, scope).code;
		const auto if_branch   = expression(*expr.if_branch, info, scope).code;
		const auto else_branch = expression(*expr.else_branch, info, scope).code;
		
		const auto code = conditional(
			name,
			condition,
			if_branch,
			else_branch);
		
		return ExprCode{code};
	}
}