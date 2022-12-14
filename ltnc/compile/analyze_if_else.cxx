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
		
		if(has_else_branch(stmt)) {
			MinorScope else_scope{&scope};
			
			const auto else_branch = analyze_statement(*stmt.else_branch, info, else_scope);
			
			const auto total_var_count = std::max(
				if_branch->local_vars,
				else_branch->local_vars);

			return std::make_unique<sst::IfElse>(
				total_var_count, false,
				std::move(condition),
				std::move(if_branch),
				std::move(else_branch)
			);
		}
		else {
			return std::make_unique<sst::IfElse>(
				if_branch->local_vars, false,
				std::move(condition),
				std::move(if_branch),
				nullptr
			);
		}
	}
}