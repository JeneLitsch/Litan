#include "compiling.hxx"

namespace ltn::c::compile {
	std::string makeJumpId(const std::string_view name, CompilerInfo & info) {
		std::stringstream ss;
		ss << name << info.jumpMarkCounter++;
		return ss.str();
	}

	StmtCode ifElse(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope) {
		const auto idIfEnd = makeJumpId("IF_END", info);
		const auto condition = compile::expression(*stmt.condition, info, scope);
		const auto ifBranch = compile::statement(*stmt.ifBranch, info, scope);
		if(stmt.elseBranch) {
			const auto elseBranch = compile::statement(*stmt.elseBranch, info, scope);
			const auto idElse = makeJumpId("IF_ELSE", info);
			std::stringstream ss;
			ss << condition.code;
			ss << inst::ifelse(idElse);

			ss << ifBranch.code;
			ss << inst::jump(idIfEnd);

			ss << inst::jumpmark(idElse);
			ss << elseBranch.code;
			ss << inst::jump(idIfEnd);

			ss << inst::jumpmark(idIfEnd);
			return {ss.str()};
		}
		else {
			std::stringstream ss;
			ss << condition.code;
			ss << inst::ifelse(idIfEnd);

			ss << ifBranch.code;
			ss << inst::jumpmark(idIfEnd);
			return {ss.str()};
		}

	}
}