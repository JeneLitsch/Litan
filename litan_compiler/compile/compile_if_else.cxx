#include "compile.hxx"
#include "litan_compiler/sst/stmt/IfElse.hxx"
#include "litan_compiler/sst/stmt/NoOp.hxx"

namespace ltn::c {
	bool has_else_branch(const sst::stmt::IfElse & stmt) {
		return stmt.else_branch && (!as<sst::stmt::NoOp>(*stmt.else_branch));
	}



	InstructionBuffer compile_stmt(const sst::stmt::IfElse & stmt) {

		const auto condition = compile_expression(*stmt.condition);
		const auto if_branch = compile_statement(*stmt.if_branch);
		
		const auto name = make_jump_id("IF");

		if(has_else_branch(stmt)) {
			const auto else_branch = compile_statement(*stmt.else_branch);
			
			return compile_conditional(name, condition, if_branch, &else_branch);
		}
		else {
			return compile_conditional(name, condition, if_branch, nullptr);
		}
	}
}