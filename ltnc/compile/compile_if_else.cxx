#include "compile.hxx"

namespace ltn::c::compile {
	bool has_else_branch(const ast::IfElse & stmt) {
		return stmt.else_branch && (!as<ast::DoNothing>(*stmt.else_branch));
	}


	StmtCode if_else(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope) {
		// Separate scopes for branches
		Scope if_scope{&scope};
		Scope else_scope{&scope};

		// compiles parts
		const auto idIfEnd = make_jump_id("IF_END");
		const auto condition = expression(*stmt.condition, info, scope);
		const auto if_branch = statement(*stmt.if_branch, info, if_scope);
		
		// with else
		if(has_else_branch(stmt)) {
			const auto else_branch = statement(*stmt.else_branch, info, else_scope);
			const auto idElse = make_jump_id("IF_ELSE");
			std::stringstream ss;
			ss << condition.code;
			ss << inst::ifelse(idElse);

			ss << if_branch.code;
			ss << inst::jump(idIfEnd);

			ss << inst::jumpmark(idElse);
			ss << else_branch.code;
			ss << inst::jump(idIfEnd);

			ss << inst::jumpmark(idIfEnd);
			return {ss.str(), std::max(if_branch.var_count, else_branch.var_count)};
		}
		// without else
		else {
			std::stringstream ss;
			ss << condition.code;
			ss << inst::ifelse(idIfEnd);

			ss << if_branch.code;
			ss << inst::jumpmark(idIfEnd);
			return {ss.str(), if_branch.var_count};
		}

	}
}