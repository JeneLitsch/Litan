#include "compile.hxx"

namespace ltn::c::compile {
	
	// creates a jump label
	std::string make_jump_id(const std::string_view name, CompilerInfo & info) {
		std::stringstream ss;
		ss << name << info.jump_mark_counter++;
		return ss.str();
	}

	StmtCode if_else(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope) {
		// Separate scopes for branches
		Scope if_scope{&scope};
		Scope else_scope{&scope};

		// compiles parts
		const auto idIfEnd = make_jump_id("IF_END", info);
		const auto condition = expression(*stmt.condition, info, scope);
		const auto if_branch = statement(*stmt.if_branch, info, if_scope);
		
		// with else
		if(stmt.else_branch) {
			const auto else_branch = statement(*stmt.else_branch, info, else_scope);
			const auto idElse = make_jump_id("IF_ELSE", info);
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