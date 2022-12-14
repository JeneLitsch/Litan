#include "compile.hxx"

namespace ltn::c {
	bool has_else_branch(const ast::IfElse & stmt) {
		return stmt.else_branch && (!as<ast::DoNothing>(*stmt.else_branch));
	}


	sst::stmt_ptr analyze_stmt(
		const ast::IfElse & stmt,
		CompilerInfo & info,
		Scope & scope) {
		MinorScope if_scope{&scope};
		
		const auto condition = analyze_expression(*stmt.condition, info, scope);
		const auto if_branch = analyze_statement(*stmt.if_branch, info, if_scope);
		
		const auto name = make_jump_id("IF");

		if(has_else_branch(stmt)) {
			MinorScope else_scope{&scope};
			
			const auto else_branch = analyze_statement(*stmt.else_branch, info, else_scope);
			
			const auto code = analyze_conditional(
				name,
				condition.code,
				if_branch.code,
				&else_branch.code);

			const auto total_var_count = std::max(
				if_branch.var_count,
				else_branch.var_count);

			return {code, total_var_count};
		}
		else {
			const auto code = analyze_conditional(
				name,
				condition.code,
				if_branch.code,
				nullptr);

			return {code, if_branch.var_count};
		}
	}
}