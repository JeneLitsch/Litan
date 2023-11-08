#include "analyze.hxx"
#include "ltnc/sst/stmt/IfElse.hxx"

namespace ltn::c {
	bool has_else_branch(const ast::IfElse & stmt) {
		return stmt.else_branch && (!as<ast::NoOp>(*stmt.else_branch));
	}


	sst::stmt_ptr analyze_stmt(const ast::IfElse & stmt, Scope & scope) {
		MinorScope if_scope{&scope};
		
		auto condition = analyze_expression(*stmt.condition, scope);
		auto if_branch = analyze_statement(*stmt.if_branch, if_scope);
		
		if(has_else_branch(stmt)) {
			MinorScope else_scope{&scope};
			
			auto else_branch = analyze_statement(*stmt.else_branch, else_scope);
			
			return sst::if_else(
				std::move(condition),
				std::move(if_branch),
				std::move(else_branch)
			);
		}
		else {
			return sst::if_else(
				std::move(condition),
				std::move(if_branch),
				nullptr
			);
		}
	}
}