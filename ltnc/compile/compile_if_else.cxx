#include "compile.hxx"

namespace ltn::c {
	bool has_else_branch(const sst::IfElse & stmt) {
		return stmt.else_branch && (!as<ast::DoNothing>(*stmt.else_branch));
	}


	InstructionBuffer compile_stmt(const sst::IfElse & stmt) {

		const auto condition = compile_expression(*stmt.condition);
		const auto if_branch = compile_statement(*stmt.if_branch);
		
		const auto name = make_jump_id("IF");

		if(has_else_branch(stmt)) {
			const auto else_branch = compile_statement(*stmt.else_branch);
			
			return compile_conditional(name, condition, if_branch, &else_branch);
		}
		else {
			const auto code = compile_conditional(name, condition, if_branch, nullptr);
		}
	}
}