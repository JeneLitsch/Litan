#include "compile.hxx"

namespace ltn::c::compile {
	bool has_else_branch(const ast::IfElse & stmt) {
		return stmt.else_branch && (!as<ast::DoNothing>(*stmt.else_branch));
	}


	StmtCode if_else(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope) {
		Scope if_scope{&scope};

		const auto name = make_jump_id("IF");
		const auto condition = expression(*stmt.condition, info, scope);
		const auto if_branch = statement(*stmt.if_branch, info, if_scope);

		if(has_else_branch(stmt)) {
			Scope else_scope{&scope};
			
			const auto else_branch = statement(*stmt.else_branch, info, else_scope);
			
			const auto code = conditional(
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
			const auto code = conditional(
				name,
				condition.code,
				if_branch.code,
				nullptr);

			return {code, if_branch.var_count};
		}

	}
}