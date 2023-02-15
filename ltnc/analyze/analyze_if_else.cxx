#include "analyze.hxx"

namespace ltn::c {
	bool has_else_branch(const ast::IfElse & stmt) {
		return stmt.else_branch && (!as<ast::DoNothing>(*stmt.else_branch));
	}


	sst::stmt_ptr analyze_stmt(
		const ast::IfElse & stmt,
		Context & context,
		Scope & scope) {
		MinorScope if_scope{&scope};
		
		auto condition = analyze_expression(stmt.condition, context, scope);
		auto if_branch = analyze_statement(*stmt.if_branch, context, if_scope);
		
		if(has_else_branch(stmt)) {
			MinorScope else_scope{&scope};
			
			auto else_branch = analyze_statement(*stmt.else_branch, context, else_scope);
			
			return std::make_unique<sst::IfElse>(
				std::move(condition),
				std::move(if_branch),
				std::move(else_branch)
			);
		}
		else {
			return std::make_unique<sst::IfElse>(
				std::move(condition),
				std::move(if_branch),
				nullptr
			);
		}
	}
}