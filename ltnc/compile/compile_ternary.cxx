#include "compile.hxx"
#include "ltnc/sst/expr/Ternary.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::Ternary & expr) {
		const auto name        = make_jump_id("TERNARY");
		const auto condition   = compile_expression(*expr.condition);
		const auto if_branch   = compile_expression(*expr.if_branch);
		const auto else_branch = compile_expression(*expr.else_branch);
		
		return compile_conditional(
			name,
			condition,
			if_branch,
			&else_branch
		);
	}
}