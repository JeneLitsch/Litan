#include "analyze.hxx"
#include "ltnc/ast/stmt/IfElse.hxx"
#include "ltnc/ast/stmt/NoOp.hxx"
#include "ltnc/sst/stmt/IfElse.hxx"

#include "ltnc/scoping/BlockScope.hxx"

namespace ltn::c {
	bool has_else_branch(const ast::stmt::IfElse & stmt) {
		return stmt.else_branch && (!as<ast::stmt::NoOp>(*stmt.else_branch));
	}


	sst::stmt_ptr analyze_stmt(const ast::stmt::IfElse & stmt, Scope & scope) {
		BlockScope if_scope{&scope};
		
		auto condition = analyze_expression(*stmt.condition, scope);
		auto if_branch = analyze_statement(*stmt.if_branch, if_scope);
		
		if(has_else_branch(stmt)) {
			BlockScope else_scope{&scope};
			
			auto else_branch = analyze_statement(*stmt.else_branch, else_scope);
			
			return sst::stmt::if_else(
				std::move(condition),
				std::move(if_branch),
				std::move(else_branch)
			);
		}
		else {
			return sst::stmt::if_only(
				std::move(condition),
				std::move(if_branch)
			);
		}
	}
}